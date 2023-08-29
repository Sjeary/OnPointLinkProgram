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
#include <QMessageBox>

servercore::servercore(TcpServer *ptcpserver, QObject *parent) : QObject(parent)
{
    tp = ptcpserver;
    connect(tp, &TcpServer::received, this, &servercore::switchFunction);
    connect(tp, &TcpServer::disconnected, this, &servercore::offline);
    db = QSqlDatabase::addDatabase("QODBC");
    db.setPort(3306);
    db.setDatabaseName("mysql");//不同电脑连接不同的数据库的时候记得改
    db.setUserName("root");
    db.setPassword("7979");
    db.open();
    if(!db.isOpen())qDebug()<<"Dont Connected"<<endl<<db.lastError().text()<<endl;
}

void servercore::offline(QTcpSocket *psocket)
{
//更新socketmap，将登出用户剔除
    for (auto it = socketmap.begin(); it != socketmap.end(); ++it) {
        if (it.value() == psocket) {
            socketmap.erase(it);
            break; // Assuming there's only one matching value
        }
    }
}

void servercore::switchFunction(QTcpSocket *psocket)
{
    //swichFunction(jsonObject["transType"])
    qDebug() << "switchFunction:" << endl;
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
    stringMap.insert("SendMessageRequest",15);
    stringMap.insert("TargetMessageRequest", 17);
    stringMap.insert("MessageReadedRequest", 19);
    stringMap.insert("FileListRequest", 21);
    stringMap.insert("FileRequest", 23);
    stringMap.insert("SendFriendRequestToServer", 25) ;
    stringMap.insert("SendResultFromReceiverClientToServer", 27) ;
    stringMap.insert("SendDeleteFriendRequest", 29) ;
    stringMap.insert("ChangeFriendDevide", 31) ;
    stringMap.insert("SendCreateGroupRequest", 33) ;
    stringMap.insert("SendGroupMessage", 33) ;
    QString type = obj["transType"].toString();
    switch (stringMap.value(type)){
    case 1 : RegRequest(obj);break;
    case 3 : EnterRequest(obj);break;
    case 5 : AccountInfoRequest(obj);break;
    case 7 : FriendListRequest(obj);break;
    case 9 : GroupListRequest(obj);break;
    case 11 : UserInfoRequest(obj);break;
    case 13 : GroupInfoRequest(obj);break;
    case 15 : SendTxtMessageRequest(obj);break;
//    case 17 : TargetMessageRequest(obj);break;
//    case 19 : MessageReadedRequest(obj);break;
//    case 21 : FileListRequest(obj);break;
//    case 23 : FileRequest(obj);break;
    case 25 : SendFriendRequestToServer(obj);break;
    case 27 : SendResultFromReceiverClientToServer(obj);break;
    case 29 : SendDeleteFriendRequest(obj);break;
    case 31 : ChangeFriendDevide(obj);break;
    case 33 : SendCreateGroupRequest(obj);break;
    case 35 : SendGroupMessage(obj);break;
    }
}
void servercore::SendGroupMessage(QJsonObject &jsonObj)
{
    int GroupOID = jsonObj["GroupOID"].toInt();
    int SenderMemberOID = jsonObj["SenderMemberOID"].toInt();
    QString Content = jsonObj["Content"].toString();
    QString Type = jsonObj["Type"].toString();


    QSqlQuery query(db);
    //查询发送者的姓名
    query.prepare(QString("SELECT * FROM account WHERE OID = :SenderMemberOID"));
    query.bindValue(":SenderMemberOID",SenderMemberOID);
    query.exec();
    query.next();
    QString SenderName = query.value("Name").toString();

    if(!query.exec(QString("SELECT * FROM ga WHERE GroupOID = %1").arg(GroupOID)))
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        return ;
    }
    int cnt = 0;
    while(query.next())
    {

        int mOID = query.value("MemberOID").toInt();
        // 发送给在线用户
        QJsonObject returnJsonObject;
        QDateTime SendTime = QDateTime::currentDateTime();
        returnJsonObject["SenderName"]=SenderName;
        returnJsonObject["SenderMemberOID"]=SenderMemberOID;
        returnJsonObject["GroupOID"]=GroupOID;
        returnJsonObject["transType"]="SendGroupMessage";
        returnJsonObject["Type"]=Type;
        returnJsonObject["Content"]=Content;
        returnJsonObject["SendTime"] = SendTime.toString();
        if(socketmap.contains(mOID))
        {
            cnt++;
            QHostAddress targetip = socketmap.value(mOID)->peerAddress();
            quint16 targetport = socketmap.value(mOID)->peerPort();
            QJsonDocument returnJsonDocument(returnJsonObject);
            QByteArray returnJsonData = returnJsonDocument.toJson();
            qDebug()<<returnJsonData;
            tp->send(targetip, targetport, returnJsonData);
        }
    }
    QJsonObject returnJsonObject;
    QDateTime SendTime = QDateTime::currentDateTime();
    returnJsonObject["SenderName"]=SenderName;
    returnJsonObject["SenderMemberOID"]=SenderMemberOID;
    returnJsonObject["GroupOID"]=GroupOID;
    returnJsonObject["transType"]="SendGroupMessage";
    returnJsonObject["Type"]=Type;
    returnJsonObject["Content"]=Content;
    returnJsonObject["SendTime"] = SendTime.toString();
    returnJsonObject["CountOfReviver"] = cnt;
}
void servercore::SendCreateGroupRequest(QJsonObject &jsonObj)
{
    QString Name = jsonObj["Name"].toString();
    QJsonArray memberlist = jsonObj["menmberOID"].toArray();
    // 将本机OID也加入
    {
        int OID = jsonObj["HostOID"].toInt();
        QJsonObject obj;
        obj["OID"] = OID;
        memberlist.append(obj);
    }
    // 在group表建立一个群
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM `group`");
    if(!query.exec())
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        return ;
    }
    int OID = 0;
    if(query.next())
    {
        int rowCount = query.value(0).toInt();
        qDebug()<<"Number of the row is "<<rowCount;
        OID = rowCount+100001;
        if(OID>999999||OID<100000)
        {
            qDebug()<<"OID wrong"<<endl;
        }
        query.prepare("INSERT INTO `group` (OID,Name) VALUES(:OID,:Name)");
        query.bindValue(":OID",OID);
        query.bindValue(":Name",Name);
        if (!query.exec()) {
                qDebug() << "Database insertion error:" << query.lastError().text();
                return ;
            }
    }
    // 更新ga表
    foreach (auto var, memberlist) {
        QJsonObject m = var.toObject();
        int mOID = m["OID"].toInt();
        query.prepare("INSERT INTO ga(GroupOID, MemberOID) VALUES(:GroupOID, :MemberOID)");
        query.bindValue(":GroupOID",OID);
        query.bindValue(":MemberOID",mOID);
        if(!query.exec())
        {
            qDebug()<<"Query ERROR: "<<query.lastError().text();
            return ;
        }
    }
    // 最后返回一个群的OID
    {
        QJsonObject returnJsonObject;
        returnJsonObject["GroupOID"]=OID;
        returnJsonObject["transType"]="CreateGroupResult";//文件类型
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
    }
}

void servercore::returnChangeFriendDevide(int OID1, int OID2, bool Status, QString log, QString transType)
{
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=OID1;
    returnJsonObject["OID2"]=OID2;
    returnJsonObject["transType"]=transType;
    returnJsonObject["Status"]=Status;
    returnJsonObject["log"]=log;
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
}
void servercore::ChangeFriendDevide(QJsonObject &jsonObj)
{
    int OID1 = jsonObj["OID1"].toInt();
    int OID2 = jsonObj["OID2"].toInt();
    QString Devide = jsonObj["Devide"].toString();

    QSqlQuery query(db);
    query.prepare("UPDATE friend SET Devide = :Devide WHERE OID1 = :OID1 AND OID2=:OID2");
    query.bindValue(":OID1",OID1);
    query.bindValue(":OID2",OID2);
    query.bindValue(":Devide",Devide);

    if (!query.exec())
    {
        qDebug() << "Database UPDATE Friend Devide error:" << query.lastError().text();
        returnChangeFriendDevide(OID1,OID2,0,"Database UPDATE Friend Devide error:"+query.lastError().text(),"returnChangeFriendDevide");
        return;
    }
    returnChangeFriendDevide(OID1,OID2,1,"UPDATE Friend Devide Succeed!","returnChangeFriendDevide");
}
void servercore::returnSendDeleteFriendRequest(int OID1,int OID2,bool Status,QString log,QString Devide,QString transType)
{
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=OID1;
    returnJsonObject["OID2"]=OID2;
    returnJsonObject["transType"]=transType;
    returnJsonObject["Status"]=Status;
    returnJsonObject["log"]=log;
    returnJsonObject["Devide"]=Devide;
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);

}
void servercore::SendDeleteFriendRequest(QJsonObject &jsonObj)
{
    int OID1 = jsonObj["OID1"].toInt();
    int OID2 = jsonObj["OID2"].toInt();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM friend WHERE OID1 = :OID1 AND OID2 = :OID2 ;");
    query.bindValue(":OID1",OID1);
    query.bindValue(":OID2",OID2);
    QString Devide = query.value("Devide").toString();


    query.prepare("DELETE FROM friend WHERE OID1 = :OID1 AND OID2 = :OID2;");
    query.bindValue(":OID1",OID1);
    query.bindValue(":OID2",OID2);
    if (!query.exec())
    {
        qDebug() << "Database DELETE friend error:" << query.lastError().text();
        returnSendDeleteFriendRequest(OID1,OID2,0,"Database DELETE friend error:"+query.lastError().text(),Devide,"returnSendDeleteFriendRequest");
        return;
    }
    query.prepare("DELETE FROM friend WHERE OID1 = :OID1 AND OID2 = :OID2;");
    query.bindValue(":OID1",OID2);
    query.bindValue(":OID2",OID1);
    if (!query.exec())
    {
        qDebug() << "Database DELETE friend error:" << query.lastError().text();
        returnSendDeleteFriendRequest(OID1,OID2,0,"Database DELETE friend error:"+query.lastError().text(),Devide,"returnSendDeleteFriendRequest");
        return;
    }
    returnSendDeleteFriendRequest(OID1,OID2,1,"Delete Friend Succeed!",Devide,"returnSendDeleteFriendRequest");
}

void servercore::returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value, QString SenderName, QString Content)
{
    // 还没实现文件消息的传输

    QJsonObject returnJsonObject;
    returnJsonObject["Statues"]=Status;
    returnJsonObject["MID"]=MID;
    returnJsonObject["SenderName"]=SenderName;
    returnJsonObject["SenderOID"]=SenderOID;
    returnJsonObject["TargetOID"]=TargetOID;
    returnJsonObject["transType"]="SendMessageResult";
    returnJsonObject["Type"]=Type;
    returnJsonObject["Value"]=Value;
    returnJsonObject["Content"]=Content;
    if (Status)
    {
        QHostAddress targetip = socketmap.value(TargetOID)->peerAddress();
        quint16 targetport = socketmap.value(TargetOID)->peerPort();
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(targetip, targetport, returnJsonData);
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
    QString Content = jsonObj["Content"].toString();

    QSqlQuery query(db);
    //查询发送者的姓名
    query.prepare(QString("SELECT * FROM account WHERE OID = :SenderOID"));
    query.bindValue(":SenderOID",SenderOID);
    query.exec();
    query.next();
    QString SenderName = query.value("Name").toString();

    int MID = -100;
    if (!query.exec(QString("SELECT MAX(MID) AS MaxMID FROM message")))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    if (query.next()) {
        MID = query.value("MaxMID").toInt();
        qDebug()<<query.value("MaxMID");
        qDebug() << "Maximum value of" << "MID" << "is:" << MID++;
    }
    //判断消息类型是文本（Txt）还是文件（Document），文本的Value为消息内容，文件的Value是文件名，Content是内容进行编码后的二进制流

    QTcpSocket* flag = socketmap.value(TargetOID, nullptr);

    if (Type == "Txt")
    {
        if (flag)
        {
            returnSendTextMessageResult(1, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
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
                returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
                return;
            }
            returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
        }
    }
    else
    {
        QString saveFilePath = filepath + Value;
        if (!saveFilePath.isEmpty()) {
            QFile saveFile(saveFilePath);
            if (saveFile.open(QIODevice::ReadWrite)) {
                saveFile.write(QByteArray::fromBase64(Content.toUtf8()));
                saveFile.close();
                qDebug() << "File saved successfully.";
            } else {
                QMessageBox::critical(nullptr, "Error", "Could not save file.");
            }
        }
        if (flag)
        {
            returnSendTextMessageResult(1, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
        }
        else
        {
            QDateTime SendTime = QDateTime::currentDateTime();
            query.prepare("INSERT INTO message (MID,Type,SenderOID,TargetOID,SendTime,Readed,Value) VALUES(:MID,:Type,:SenderOID,:TargetOID,:SendTime,:Readed,:Value)");
            query.bindValue(":MID", MID);
            query.bindValue(":Type", Type);
            query.bindValue(":SenderOID", SenderOID);
            query.bindValue(":TargetOID", TargetOID);
            query.bindValue(":SendTime", SendTime);
            query.bindValue(":Readed", 0);
            query.bindValue(":Value", saveFilePath);
            if (!query.exec())
            {
                qDebug() << "Database insertion error:" << query.lastError().text();
                returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
                return;
            }
            returnSendTextMessageResult(0, MID, SenderOID, TargetOID, Type, Value,SenderName,Content);
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

    // 第一步 登录
    qDebug() << "EnterRequest:" << jsonObj["OID"].toString()<< endl;
    int OID = jsonObj["OID"].toInt();
    QString Password = jsonObj["Password"].toString();
    socketmap.insert(OID, sp);
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
        // 情况1：考虑到已经是好友的情况
        qDebug()<<1123;
        QSqlQuery query2(db);
        query2.prepare("SELECT * FROM friend WHERE OID1 = :OID1 AND OID2 = :OID2");
        query2.bindValue(":OID1", SenderOID);
        query2.bindValue(":OID2", TargetOID);
        if(!query2.exec())
        {
            qDebug()<<"Query exec() ERROR: "<<query2.lastError().text();
            ProcessFriendRequestResult(SenderOID,TargetOID,0,"Query exec() ERROR: "+query2.lastError().text());
            return ;
        }
        qDebug()<<14354123;
        if(query2.size()!=-1)
        {
            qDebug()<<"Friend Already! 已经是您的好友！";
            ProcessFriendRequestResult(SenderOID,TargetOID,0,"Friend Already! 已经是您的好友！");
            return ;
        }
        else if(socketmap.contains(TargetOID))
        {
            QSqlQuery query2(db);
            int FRID = 0;
            qDebug()<<123123;
            if (!query2.exec(QString("SELECT MAX(FRID) AS MaxFRID FROM friendrequest")))
            {
                qDebug()<<5467;
                qDebug() << "Query failed:" << query2.lastError().text();
            }
            if (query2.next()) {
                qDebug()<<7583;
                FRID = query2.value("MaxFRID").toInt();
                qDebug()<<query2.value("MaxFRID");
                qDebug() << "Maximum value of" << "FRID" << "is:" << FRID++;
            }

            query.prepare("INSERT INTO friendrequest (FRID, SenderOID,TargetOID,ApplicationMessage) VALUES (:FRID,:SenderOID,:TargetOID,:RequestMessage);");
            query.bindValue(":FRID",FRID);
            query.bindValue(":SenderOID",SenderOID);
            query.bindValue(":TargetOID",TargetOID);
            query.bindValue(":RequestMessage",RequestMessage);
            qDebug()<<187;
            if(!query.exec())
            {
                qDebug()<<"Query exec() ERROR: "<<query.lastError().text();
                ProcessFriendRequestResult(SenderOID,TargetOID,0,"Query exec() ERROR: "+query.lastError().text());
                return ;
            }

            qDebug()<<109876543;
            ProcessFriendRequestResult(SenderOID,TargetOID,1,"请求成功发送给服务器");
            qDebug()<<749796;
            SendRequestToReceiverClient(SenderOID,TargetOID,RequestMessage);//发给目标客户端
            qDebug()<<27856793;
        }
        else // 情况2：对方不在线需要存起来
        {
            qDebug()<<76597;
            StoreOfflineFriendRequest(SenderOID, TargetOID, RequestMessage);
        }
    }
    else
    {
        qDebug()<<"No Target Person 查无此人";
        ProcessFriendRequestResult(SenderOID,TargetOID,0,"No Target Person 查无此人：");
        return ;
    }
}

void servercore::StoreOfflineFriendRequest(int SenderOID, int TargetOID, QString ApplicationMessage)
{
    QSqlQuery query(db);
    qDebug()<<"offlinesdfdasdf";
//    query.prepare(QString("SELECT * FROM friendrequest WHERE SenderOID = %1 AND TargetOID = %2").arg(SenderOID).arg(TargetOID));
//    if(!query.exec())
//    {
//        qDebug()<<"Query exec() ERROR: "<<query.lastError().text();
//        return ;
//    }
    // 如果没有存储过这条信息才行
    //if(query.size() == -1)
    {
        int FRID = 0;
        if (!query.exec(QString("SELECT MAX(FRID) AS MaxFRID FROM friendrequest")))
        {
            qDebug() << "Query failed:" << query.lastError().text();
        }
        if (query.next()) {
            FRID = query.value("MaxFRID").toInt();
            qDebug()<<query.value("MaxFRID");
            qDebug() << "Maximum value of" << "FRID" << "is:" << FRID++;
        }
        query.prepare("INSERT INTO friendrequest (FRID, SenderOID, TargetOID, ApplicationMessage) VALUES (:FRID,:SenderOID,:TargetOID,:ApplicationMessage);");
        query.bindValue(":FRID", FRID);
        query.bindValue(":SenderOID", SenderOID);
        query.bindValue(":TargetOID", TargetOID);
        query.bindValue(":ApplicationMessage", ApplicationMessage);
        if(!query.exec())
        {
            qDebug()<<"Query exec() ERROR: "<<query.lastError().text();
            return ;
        }
    }
}

void servercore::SendRequestToReceiverClient(int SenderOID,int TargetOID,QString RequestMessage)
{
    //读取目标ip
    QHostAddress targetip = socketmap.value(TargetOID)->peerAddress();
    quint16 targetport = socketmap.value(TargetOID)->peerPort();
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=SenderOID;
    returnJsonObject["OID2"]=TargetOID;
    returnJsonObject["RequestMessage"]=RequestMessage;
    returnJsonObject["transType"]="SendRequestToReceiverClient";//文件类型
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    qDebug()<<targetip<<" "<<defalutport;
    tp->send(targetip, targetport, returnJsonData);
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
        query.prepare("INSERT INTO friend (OID1,OID2,Devide) VALUES (:SenderOID,:TargetOID,:Devide);");
        query.bindValue(":SenderOID",SenderOID);
        query.bindValue(":TargetOID",TargetOID);
        query.bindValue(":Devide","我的好友");
        query.exec();
        //双向好友
        query.prepare("INSERT INTO friend (OID1,OID2,Devide) VALUES (:SenderOID,:TargetOID,:Devide);");
        query.bindValue(":SenderOID",TargetOID);
        query.bindValue(":TargetOID",SenderOID);
        query.bindValue(":Devide","我的好友");
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
    QHostAddress targetip = socketmap.value(TargetOID)->peerAddress();
    quint16 targetport = socketmap.value(TargetOID)->peerPort();
    QJsonObject returnJsonObject;
    returnJsonObject["OID1"]=SenderOID;
    returnJsonObject["OID2"]=TargetOID;
    returnJsonObject["ReplyMessage"]=ReplyMessage;
    returnJsonObject["Status"]=Status;
    returnJsonObject["transType"]="SendResultToApplicant";//文件类型

    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    qDebug()<<returnJsonData;
    tp->send(targetip, targetport, returnJsonData);
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
    if (!query.exec(QString("SELECT * FROM oplinkbase.friend join oplinkbase.account ON friend.OID2 =account.OID  WHERE OID1 = %1 ;").arg(OID1)))
    {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    QJsonArray jsonArray;
    while (query.next()) {
        QJsonObject jsonObject;
        jsonObject["FriendOID"] = query.value("OID2").toInt();
        jsonObject["Devide"] = query.value("Devide").toString();
        jsonObject["FriendName"] = query.value("Name").toString();
        jsonArray.append(jsonObject);
    }
    QJsonObject jsonObject2;
    jsonObject2["transType"]="FriendListResult";//文件类型
    jsonObject2["FriendList"]=jsonArray;
    QJsonDocument jsonDocument(jsonObject2);
    QByteArray jsonData = jsonDocument.toJson(QJsonDocument::Indented);
    tp->send(sp->peerAddress(), sp->peerPort(), jsonData);
    SynchronizeServerMessages(OID1);

}
void servercore::SynchronizeServerMessages(int OID)
{
    // 第二步 同步消息
    QSqlQuery query(db);
    query.prepare("SELECT * FROM message INNER JOIN account ON message.SenderOID=account.OID WHERE TargetOID = :OID;");
    query.bindValue(":OID", OID);
    if(!query.exec())
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        returnEnterResult(OID,sp->peerAddress(),0,"Query ERROR: "+query.lastError().text());
        return ;
    }
    int Size = query.size();
    qDebug()<<"Size : "<<Size;
    while(query.next())
    {
        QJsonObject returnJsonObject;
        returnJsonObject["SenderOID"]=query.value("SenderOID").toInt();
        returnJsonObject["TargetOID"]=query.value("TargetOID").toInt();
        returnJsonObject["SenderName"]=query.value("Name").toString();
        returnJsonObject["transType"]="SendMessageResult";
        returnJsonObject["Type"]="Txt";
        returnJsonObject["Value"]=query.value("Value").toString();
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
        #ifdef _WIN32
            Sleep(200); // 经过精准的测试
        #else
            usleep(200000); // 10,000 微秒 = 10 毫秒
        #endif
    }

    {
        query.prepare("DELETE FROM message WHERE TargetOID = :OID");
        query.bindValue(":OID", OID);
        if (query.exec()) {
            qDebug() << "Deletion message successful";
        } else {
            qDebug() << "Deletion message failed:" << query.lastError().text();
        }
    }
    // 第三步 同步文件

    // 第四步 同步好友申请
    query.prepare("SELECT * FROM friendrequest JOIN account ON friendrequest.SenderOID =account.OID WHERE TargetOID = :OID");
    query.bindValue(":OID", OID);
    if(!query.exec())
    {
        qDebug()<<"Query ERROR: "<<query.lastError().text();
        return ;
    }
    while(query.next())
    {
        QJsonObject returnJsonObject;
        returnJsonObject["OID1"]=query.value("SenderOID").toInt();
        returnJsonObject["OID2"]=query.value("TargetOID").toInt();
        returnJsonObject["SenderName"]=query.value("Name").toString();
        returnJsonObject["ApplicationMessage"]=query.value("ApplicationMessage").toString();
        returnJsonObject["transType"]="SendRequestToReceiverClient";
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(sp->peerAddress(), sp->peerPort(), returnJsonData);
        #ifdef _WIN32
            Sleep(200);
        #else
            usleep(200000); // 10,000 微秒 = 10 毫秒
        #endif
    }

    {
        query.prepare("DELETE  FROM friendrequest WHERE (Accepted IN(0, 1)) AND TargetOID = :OID");
        query.bindValue(":OID", OID);
        if (query.exec()) {
            qDebug() << "Deletion friendrequest successful";
        } else {
            qDebug() << "Deletion friendrequest failed:" << query.lastError().text();
        }
    }

}

void servercore::GroupListRequest(QJsonObject &jsonObj)
{
    int OID = jsonObj["OID"].toInt();
    QSqlQuery query(db);
    if (!query.exec(QString("SELECT * FROM `group`, ga WHERE MemberOID = %1").arg(OID)))
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
    if (!query.exec(QString("SELECT * FROM `group` WHERE OID = %1").arg(GroupOID)))
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
    if (!query.exec(QString("SELECT * FROM `group`, ga WHERE OID = %1 AND GroupOID = OID").arg(GroupOID)))
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
