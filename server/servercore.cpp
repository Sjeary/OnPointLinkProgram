/*
 * ============================
 * servercore.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 ServerCore 类的成员函数
 * ============================
 *
*/

#include "servercore.h"
#include "tcpserver.h"
#include <QString>
#include <QMap>
#include <QDateTime>

servercore::servercore(TcpServer *ptcpserver, QObject *parent) : QObject(parent)
{
    tp = ptcpserver;
    connect(tp, &TcpServer::received, this, &servercore::switchFunction);
    connect(tp, &TcpServer::disconnected, this, &servercore::offline);
    db = QSqlDatabase::addDatabase("QODBC");
    db.setPort(3306);
    db.setDatabaseName("oplinkbase");//不同电脑连接不同的数据库的时候记得改
    //db.setUserName("root");
    //db.setPassword("7979");
    db.open();
    if(!db.isOpen())qDebug()<<"Dont Connected"<<endl<<db.lastError().text()<<endl;
}

void servercore::offline(QTcpSocket *psocket)
{
//更新ipmap，将登出用户剔除
    for (auto it = ipmap.begin(); it != ipmap.end(); ++it) {
        if (it.value() == psocket->peerAddress()) {
            ipmap.erase(it);
            break; // Assuming there's only one matching value
        }
    }
}

void servercore::switchFunction(QTcpSocket *psocket)
{
    //swichFunction(jsonObject["transType"])
    sp = psocket;
    QByteArray data = psocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QMap <QString, int> stringMap;
    stringMap.insert("RegRequest", 1);
    stringMap.insert("EnterRequest", 3);
    stringMap.insert("AccountInfoRequest", 5);
    stringMap.insert("FriendListRequest", 7);
    stringMap.insert("GroupListRequest", 9);
    stringMap.insert("UserInfoRequest", 11);
    stringMap.insert("GroupInfoRequest", 13);
    stringMap.insert("SendTxtMessageRequest", 15);
    stringMap.insert("TargetMessageRequest", 17);
    stringMap.insert("MessageReadedRequest", 19);
    stringMap.insert("FileListRequest", 21);
    stringMap.insert("FileRequest", 23);
    stringMap.insert("SendFriendRequestToServer", 25) ;
    QString type = obj["transType"].toString();
    switch (stringMap.value(type)){
    case 1 : RegRequest(obj);break;
    case 3 : EnterRequest(obj);break;
    case 5 : AccountInfoRequest(obj);break;
    case 7 : FriendListRequest(obj);break;
//    case 9 : GroupListRequest(obj);break;
//    case 11 : UserInfoRequest(obj);break;
//    case 13 : GroupInfoRequest(obj);break;
    case 15 : SendTxtMessageRequest(obj);break;
//    case 17 : TargetMessageRequest(obj);break;
//    case 19 : MessageReadedRequest(obj);break;
//    case 21 : FileListRequest(obj);break;
//    case 23 : FileRequest(obj);break;
    case 25 : SendFriendRequestToServer(obj);break;
    }
}

void servercore::returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value)
{
    // 还没实现文件消息的传输
    QHostAddress targetip = ipmap.value(TargetOID);
    QJsonObject returnJsonObject;
    returnJsonObject["Statues"]=Status;
    returnJsonObject["MID"]=MID;
    returnJsonObject["SenderOID"]=SenderOID;
    returnJsonObject["TargetOID"]=TargetOID;
    returnJsonObject["transType"]="SendMessageResult";
    returnJsonObject["Type"]=Type;
    returnJsonObject["Value"]=Value;
    if (Status)
    {
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(targetip, defalutport, returnJsonData);
    }
    else
    {
        returnJsonObject["Value"]="对方不在线！";
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
    }
}

void servercore::SendTxtMessageRequest(QJsonObject &jsonObj)
{
    int SenderOID = jsonObj["SenderOID"].toInt();
    int TargetOID = jsonObj["TargetOID"].toInt();
    QString Type = jsonObj["Type"].toString();
    QString Value = jsonObj["Value"].toString();

    QSqlQuery query(db);
    int MID = 0;
    if (!query.exec(QString("SELECT MAX(%1) FROM my_table").arg(MID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    if (query.next()) {
        MID = query.value(0).toInt();
        qDebug() << "Maximum value of" << "MID" << "is:" << MID++;
    }
    //判断消息类型是文本（Txt）还是文件（Doc），文本的Value为消息内容
    if (Type == "Txt")
    {
        if (ipmap.contains(TargetOID))
        {
            returnSendTextMessageResult(1, MID, SenderOID, TargetOID, Type, Value);
        } else
        {
            QDateTime SendTime = QDateTime::currentDateTime();
            query.prepare("INSERT INTO message (MID,Type,SenderOID,TargetOID,SendTime,Readed,Value) VALUES(:MID,:Type,:SenderOID,:TargetOID,:SendTime,:Readed,:Value)");
            query.bindValue(":MID", MID);
            query.bindValue(":Type", Type);
            query.bindValue(":SenderOID", SenderOID);
            query.bindValue(":TargetOID", TargetOID);
            query.bindValue(":SendTime", SendTime);
            query.bindValue(":Readed", 0);
            query.bindValue(":Value", Value);
            if (!query.exec())
            {
                qDebug() << "Database insertion error:" << query.lastError().text();
                returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value);
                return;
            }
            returnSendTextMessageResult(1, MID, SenderOID, TargetOID, Type, Value);
        }
    }
    else
    {
        if (ipmap.contains(TargetOID))
        {
            returnSendTextMessageResult(1, MID, SenderOID, TargetOID, Type, Value);
        }
        else
        {
            returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value);
        }
    }
}

void servercore::returnEnterResult(int OID, QHostAddress ip, bool status, QString log)
{
    QJsonObject returnJsonObject;
    returnJsonObject["OID"]=OID;
    returnJsonObject["transType"]="EnterResult";//文件类型
    returnJsonObject["Status"]=status;//传输结果
    returnJsonObject["log"]=log;//日志
    returnJsonObject["IP"]=ip.toString();//ip
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}

void servercore::EnterRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    QString Password = jsonObj["Password"].toString();
    ipmap.insert(OID, sp->peerAddress());
    QSqlQuery query(db);
    query.prepare("SELECT * FROM account WHERE OID = :OID");
    query.bindValue(":OID", OID);

    if(!query.exec())
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        returnEnterResult(OID,sp->peerAddress(),0,"Query ERROR: "+query.lastError().text());
        return ;
    }

    if(query.next())
    {
        QString pwd = query.value("Password").toString();
        qDebug()<<"The Password is "<< pwd;
        if (pwd == Password)
        {
            returnEnterResult(OID, sp->peerAddress(), 1, "EnterSucceed!");
        } else
        {
            returnEnterResult(OID, sp->peerAddress(), 0, "EnterFailed!");
        }
    }
    return;
}

void servercore::returnRegResult(int OID,bool Status,QString log,QString Name)
{
    //回传给前端的json
    QJsonObject returnJsonObject;
    returnJsonObject["OID"]=OID;
    returnJsonObject["transType"]="RegResult";//文件类型
    returnJsonObject["Status"]=Status;//传输结果
    returnJsonObject["log"]=log;//失败日志
    returnJsonObject["Name"]=Name;//这里多加了一个name，前端可能用得上

    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    //这里少一个传回到客户端json文件的函数，但是我不知道接口怎么写
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}

void servercore::RegRequest(QJsonObject &jsonObj)
{
    /*QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&parseError);
    if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parsing error:" << parseError.errorString();
            return false;
        }
    if (!jsonDoc.isObject()) {
            qDebug() << "Invalid JSON format.";
            return false;
        }
    QJsonObject jsonObj = jsonDoc.object();
    */
    QString Name = jsonObj.value("Name").toString();
    //    QString Email = jsonObj.value("Email").toString();
    //    QString Introduction = jsonObj.value("Introduction").toString();
    //    QString BirthDay = jsonObj.value("BirthDay").toString();
    //    QString Area = jsonObj.value("Area").toString();
    //    QString Sex = jsonObj.value("Sex").toString();
    QString Password = jsonObj.value("Password").toString();
//    QString HeadImage = jsonObj.value("HeadImage").toString();

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM account");
    if(!query.exec())
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        returnRegResult(-1,false,"Query ERROR: "+query.lastError().text(),Name);
        return ;
    }
    int OID = 0;
    if(query.next())
    {
        int rowCount = query.value(0).toInt();
        qDebug()<<"Number of the row is "<<rowCount;
        OID = rowCount+10001;
        if(OID>99999||OID<10000)
        {
            qDebug()<<"OID wrong"<<endl;
            returnRegResult(-1,false,"OID wrong",Name);
        }
        query.prepare("INSERT INTO account (OID,Name,Password) VALUES(:OID,:Name,:Password)");
//        query.prepare("INSERT INTO account (OID,Name,HeadImage,Introduction,Email,BirthDay,Area,Sex,Password) VALUES(:OID,:Name,:HeadImage,:Instruction,:Email,:BirthDay,:Area,:Sex,:Password)");
        query.bindValue(":OID",OID);
        query.bindValue(":Name",Name);
//        query.bindValue(":HeadImage",HeadImage);//这里要传入文件的地址，然后另外上传文件
//        query.bindValue(":Introduction",Introduction);
//        query.bindValue(":Email",Email);
//        query.bindValue(":BirthDay",BirthDay);
//        query.bindValue(":Area",Area);
//        query.bindValue(":Sex",Sex);
        query.bindValue(":Password",Password);
        if (!query.exec()) {
                qDebug() << "Database insertion error:" << query.lastError().text();
                returnRegResult(-1,false,"Database insertion error:"+query.lastError().text(),Name);
                return ;
            }
    }
    returnRegResult(OID,true,"",Name);
    return;
}

void servercore::ProcessFriendRequestResult(int SenderOID,int TargetOID,bool Status, QString log)
{
    //回传给前端的json
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=SenderOID;
    returnJsonObject["OID2"]=TargetOID;
    returnJsonObject["transType"]="ProcessFriendRequestResult";//文件类型
    returnJsonObject["Status"]=Status;//传输结果
    returnJsonObject["log"]=log;//失败日志

    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}
void servercore::SendFriendRequestToServer(QJsonObject &jsonObj)
{
    int SenderOID = jsonObj["OID1"].toInt();
    int TargetOID = jsonObj["OID2"].toInt();
    QString RequestMessage = jsonObj["RequestMessage"].toString();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM account WHERE OID = :TargetOID;");
    query.bindValue(":TargetOID",TargetOID);
    if(!query.exec())
    {
        qDebug()<<"Query exec() ERROR: "<<query.lastError().text();
        ProcessFriendRequestResult(SenderOID,TargetOID,0,"Query exec() ERROR: "+query.lastError().text());
        return ;
    }
    if(query.size())
    {
        query.prepare("INSERT INTO friendrequest (SenderOID,TargetOID,ApplicationMessage) VALUES (:SenderOID,:TargetOID,:RequestMessage);");
        query.bindValue(":SenderOID",SenderOID);
        query.bindValue(":TargetOID",TargetOID);
        query.bindValue(":RequestMessage",RequestMessage);

        if(!query.exec())
        {
            qDebug()<<"Query exec() ERROR: "<<query.lastError().text();
            ProcessFriendRequestResult(SenderOID,TargetOID,0,"Query exec() ERROR: "+query.lastError().text());
            return ;
        }
        ProcessFriendRequestResult(SenderOID,TargetOID,1,"请求成功发送给服务器");
        SendRequestToReceiverClient(SenderOID,TargetOID,RequestMessage);//发给目标客户端
    }
    else
    {
        qDebug()<<"No Target Person 查无此人";
        ProcessFriendRequestResult(SenderOID,TargetOID,0,"No Target Person 查无此人：");
        return ;
    }
}
void servercore::SendRequestToReceiverClient(int SenderOID,int TargetOID,QString RequestMessage)
{
    //读取目标ip
    QHostAddress targetip = ipmap.value(TargetOID);
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=SenderOID;
    returnJsonObject["OID2"]=TargetOID;
    returnJsonObject["RequestMessage"]=RequestMessage;
    returnJsonObject["transType"]="SendRequestToReceiverClient";//文件类型
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(targetip, defalutport, returnJsonData);
}
void servercore::SendResultFromReceiverClientToServer(QJsonObject &jsonObj)
{
    int SenderOID = jsonObj["OID1"].toInt();
    int TargetOID = jsonObj["OID2"].toInt();
    QString ReplyMessage = jsonObj["ReplyMessage"].toString();
    bool Accepted = jsonObj["Accepted"].toBool();
    if(Accepted)
    {
        QSqlQuery query(db);
        //这里不加分组，实现默认分组，之后有需求再改
        query.prepare("INSERT INTO friend (OID1,OID2) VALUES (:SenderOID,:TargetOID);");
        query.bindValue(":SenderOID",SenderOID);
        query.bindValue(":TargetOID",TargetOID);
        query.exec();
        //双向好友
        query.prepare("INSERT INTO friend (OID1,OID2) VALUES (:SenderOID,:TargetOID);");
        query.bindValue(":SenderOID",TargetOID);
        query.bindValue(":TargetOID",SenderOID);
        query.exec();
        //更新好友申请数据库
        query.prepare("UPDATE friendrequest SET Accepted = :Accepted , ReplyMessage = :ReplyMessage WHERE SenderOID = :SenderOID AND TargetOID = :TargetOID;");
        query.bindValue(":Accepted",Accepted);
        query.bindValue(":ReplyMessage",ReplyMessage);
        query.bindValue(":SenderOID",SenderOID);
        query.bindValue(":TargetOID",TargetOID);
        query.exec();
    }
    else if(!Accepted)
    {
        QSqlQuery query(db);
        query.prepare("UPDATE friendrequest SET Accepted = :Accepted , ReplyMessage = :ReplyMessage WHERE SenderOID = :SenderOID AND TargetOID = :TargetOID;");
        query.bindValue(":Accepted",Accepted);
        query.bindValue(":ReplyMessage",ReplyMessage);
        query.bindValue(":SenderOID",SenderOID);
        query.bindValue(":TargetOID",TargetOID);
        query.exec();
    }
    SendResultToApplicant(SenderOID,TargetOID,Accepted,ReplyMessage);
}
void servercore::SendResultToApplicant(int SenderOID,int TargetOID,bool Status,QString ReplyMessage)
{
    //读取目标ip
    QHostAddress targetip = ipmap.value(TargetOID);
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=SenderOID;
    returnJsonObject["OID2"]=TargetOID;
    returnJsonObject["ReplyMessage"]=ReplyMessage;
    returnJsonObject["Status"]=Status;
    returnJsonObject["transType"]="SendResultToApplicant";//文件类型

    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(targetip, defalutport, returnJsonData);
}

void servercore::returnUserInfoResult(bool Status, int OID, QString Name, QString Instruction, QString Emai, QDate Birth)
{
    QJsonObject returnJsonObject;
    returnJsonObject["Status"]=Status;
    returnJsonObject["OID"]=OID;
    returnJsonObject["Name"]=Name;
    returnJsonObject["Instrction"]=Instruction;
    returnJsonObject["Emai"]=Emai;
    returnJsonObject["Birth"]=Birth.toString();
    returnJsonObject["transType"]="UserInfoResult";//文件类型
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}

void servercore::UserInfoRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    QSqlQuery query(db);
    if (!query.exec(QString("SELECT * FROM account WHERE OID = %1").arg(OID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    if (query.next())
    {
        bool Status = query.size();
        int OID = query.value("OID").toUInt();
        QString Name = query.value("Name").toString();
        QString Instruction = query.value("Instruction").toString();
        QString Emai = query.value("Email").toString();
        QDate Birth = query.value("Birth").toDate();
        returnAccountInfoResult(Status, OID, Name, Instruction, Emai, Birth);
    }
    else
    {
        qDebug() << "UserSerch Error!";
    }
}

void servercore::returnAccountInfoResult(bool Status, int OID, QString Name, QString Instruction, QString Emai, QDate Birth)
{
    QJsonObject returnJsonObject;
    returnJsonObject["Status"]=Status;
    returnJsonObject["OID"]=OID;
    returnJsonObject["Name"]=Name;
    returnJsonObject["Instrction"]=Instruction;
    returnJsonObject["Emai"]=Emai;
    returnJsonObject["Birth"]=Birth.toString();
    returnJsonObject["transType"]="AccountInfoResult";//文件类型
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}

void servercore::AccountInfoRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    QSqlQuery query(db);
    if (!query.exec(QString("SELECT * FROM account  WHERE OID = %1").arg(OID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    if (query.next())
    {
        bool Status = query.size();
        int OID = query.value("OID").toInt();
        QString Name = query.value("Name").toString();
        QString Instruction = query.value("Instruction").toString();
        QString Email = query.value("Email").toString();
        QDate Birth = query.value("Birth").toDate();
        returnAccountInfoResult(Status, OID, Name, Instruction, Email, Birth);
    }
    else//查无此人情况
    {
        bool Status = query.size();
        returnAccountInfoResult(Status, OID, " ", " ", " ", QDate::fromString("0000-00-00", "yyyy-MM-dd"));
        qDebug() << "AccountSearch Error!";
    }
}

void servercore::FriendListRequest(QJsonObject &jsonObj)
{
    int OID1 = jsonObj["OID"].toInt();
    QSqlQuery query(db);
    if (!query.exec(QString("SELECT * FROM account WHERE OID1 = %1").arg(OID1)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    QJsonArray jsonArray;
    QJsonObject jsonObject;

    jsonArray.append(jsonObject);
    while (query.next()) {
        QJsonObject jsonObject;
        jsonObject["FriendOID"] = query.value("OID2").toInt();
        jsonObject["Devide"] = query.value("Devide").toString();

        jsonArray.append(jsonObject);
    }
    QJsonObject jsonObject2;
    jsonObject2["transType"]="FriendListResult";//文件类型
    jsonObject2["FriendList"]=jsonArray;
    QJsonDocument jsonDocument(jsonObject2);
    QByteArray jsonData = jsonDocument.toJson(QJsonDocument::Indented);
    tp->send(sp->peerAddress(), sp->peerPort(), jsonData);
}

void servercore::GroupListRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    QSqlQuery query(db);
    if (!query.exec(QString("SELECT * FROM group, ga WHERE MemberOID = %1").arg(OID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    jsonObject["transType"]="GroupListResult";//文件类型
    jsonArray.append(jsonObject);
    while (query.next()) {
        QJsonObject jsonObject;
        jsonObject["GroupOID"] = query.value("OID").toInt();
        jsonObject["Name"] = query.value("Name").toString();
        jsonObject["Instruction"] = query.value("Instruction").toString();

        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDocument(jsonArray);
    QByteArray jsonData = jsonDocument.toJson(QJsonDocument::Indented);
    tp->send(sp->peerAddress(), sp->peerPort(), jsonData);
}

void servercore::GroupInfoRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    int GroupOID = jsonObj["GroupOID"].toInt();
    QSqlQuery query(db);
    QJsonArray jsonArray;
    // 查询群信息
    if (!query.exec(QString("SELECT * FROM group WHERE OID = %1").arg(GroupOID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    if (query.next())
    {
        QJsonObject jsonObject;
        jsonObject["OID"] = OID;
        jsonObject["GroupOID"] = query.value("OID").toInt();
        jsonObject["Name"] = query.value("Name").toString();
        jsonObject["Instruction"] = query.value("Instruction").toString();

        jsonArray.append(jsonObject);
    }
    // 查询群友信息
    if (!query.exec(QString("SELECT * FROM group, ga WHERE OID = %1 AND GroupOID = OID").arg(GroupOID)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    while (query.next()) {
        QJsonObject jsonObject;
        jsonObject["MemberOID"] = query.value("MemberOID").toInt();

        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDocument(jsonArray);
    QByteArray jsonData = jsonDocument.toJson(QJsonDocument::Indented);
    tp->send(sp->peerAddress(), sp->peerPort(), jsonData);
}



servercore::~servercore()
{
    db.close();
}
