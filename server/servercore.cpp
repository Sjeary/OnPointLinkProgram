#include "servercore.h"
#include "tcpserver.h"
#include <QString>
#include <QMap>


servercore::servercore(TcpServer *ptcpserver, QObject *parent) : QObject(parent)
{
    tp = ptcpserver;
    connect(tp, &TcpServer::received, this, &servercore::switchFunction);
    db = QSqlDatabase::addDatabase("QODBC");
    db.setPort(3306);
    db.setDatabaseName("mysql");//不同电脑连接不同的数据库的时候记得改
    db.setUserName("root");
    db.setPassword("7979");
    db.open();
    if(!db.isOpen())qDebug()<<"Dont Connected"<<endl<<db.lastError().text()<<endl;
}

void servercore::switchFunction(QTcpSocket *psocket){//swichFunction(jsonObject["transType"])
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
//    case 3 : EnterRequest(obj);break;
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
    QString Email = jsonObj.value("Email").toString();
    QString Introduction = jsonObj.value("Introduction").toString();
    QString BirthDay = jsonObj.value("BirthDay").toString();
    QString Area = jsonObj.value("Area").toString();
    QString Sex = jsonObj.value("Sex").toString();
    QString Password = jsonObj.value("Password").toString();
    QString HeadImage = jsonObj.value("HeadImage").toString();

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM account");
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
        OID = rowCount+10001;
        if(OID>99999||OID<10000)
        {
            qDebug()<<"OID wrong"<<endl;
        }
        query.prepare("INSERT INTO account (OID,Name,HeadImage,Introduction,Email,BirthDay,Area,Sex,Password) VALUES(:OID,:Name,:HeadImage,:Instruction,:Email,:BirthDay,:Area,:Sex,:Password)");
        query.bindValue(":OID",OID);
        query.bindValue(":Name",Name);
        query.bindValue(":HeadImage",HeadImage);//这里要传入文件的地址，然后另外上传文件
        query.bindValue(":Introduction",Introduction);
        query.bindValue(":Email",Email);
        query.bindValue(":BirthDay",BirthDay);
        query.bindValue(":Area",Area);
        query.bindValue(":Sex",Sex);
        query.bindValue(":Password",Password);
        if (!query.exec()) {
                qDebug() << "Database insertion error:" << query.lastError().text();
                return ;
            }

                /*
         * QString data =query.value("OID").toString();
            qDebug()<<"Data from database:"<<data;
        */
    }
    QJsonArray returnJsonArray;
    QJsonObject returnJsonObject;
    returnJsonObject["OID"]=OID;
    /*
     * 这里可以按这个格式填写其他返回值，但是考虑到注册只需要返回OID即可
    returnJsonObject["Name"]=Name;
    */
    returnJsonArray.append(returnJsonObject);
    QJsonDocument returnJsonDocument(returnJsonObject);
    QByteArray returnJsonData = returnJsonDocument.toJson();
    //这里少一个传回到客户端json文件的函数，但是我不知道接口怎么写

}
servercore::~servercore()
{
    db.close();
}
