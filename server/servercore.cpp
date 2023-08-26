#include "servercore.h"
#include "tcpserver.h"
#include <QString>
#include <QMap>
#include <QDateTime>

servercore::servercore(TcpServer *ptcpserver, QObject *parent) : QObject(parent)
{
    tp = ptcpserver;
    connect(tp, &TcpServer::received, this, &servercore::switchFunction);
    connect(tp, &TcpServer::disconnected, this, &servercore::updateipmap);
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
    QString type = obj["transType"].toString();
    switch (stringMap.value(type)){
    case 1 : RegRequest(obj);break;
    case 3 : EnterRequest(obj);break;
//    case 5 : AccountInfoRequest(obj);break;
//    case 7 : FriendListRequest(obj);break;
//    case 9 : GroupListRequest(obj);break;
//    case 11 : UserInfoRequest(obj);break;
//    case 13 : GroupInfoRequest(obj);break;
//    case 15 : SendTxtMessageRequest(obj);break;
//    case 17 : TargetMessageRequest(obj);break;
//    case 19 : MessageReadedRequest(obj);break;
//    case 21 : FileListRequest(obj);break;
//    case 23 : FileRequest(obj);break;
    }
}

void servercore::returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value)
{
    // 还没实现文件消息的传输
    if (Status)
    {
        QHostAddress targetip = ipmap.value(TargetOID);
        QJsonObject returnJsonObject;
        returnJsonObject["Statues"]=Status;
        returnJsonObject["MID"]=MID;
        returnJsonObject["SenderOID"]=SenderOID;
        returnJsonObject["TargetOID"]=TargetOID;
        returnJsonObject["transType"]="SendMessageResult";
        returnJsonObject["Type"]=Type;
        returnJsonObject["Value"]=Value;//ip
        QJsonDocument returnJsonDocument(returnJsonObject);
        QByteArray returnJsonData = returnJsonDocument.toJson();
        qDebug()<<returnJsonData;
        tp->send(targetip, defalutport, returnJsonData);
    }
    else
    {
        QString content = "Error!";
        QByteArray text = content.toUtf8();
        tp->send(sp->peerAddress(), sp->peerPort(), text);
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
        if (query.next()) {
            MID = query.value(0).toInt();
            qDebug() << "Maximum value of" << "MID" << "is:" << MID++;
        }
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
servercore::~servercore()
{
    db.close();
}
