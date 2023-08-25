#include "servercore.h"
#include "tcpserver.h"
#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>

servercore::servercore(TcpServer *ptcpserver, QObject *parent) : QObject(parent)
{
    tp = ptcpserver;
    connect(tp, &TcpServer::received, this, &servercore::switchFunction);
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
//    switch (stringMap.value(type)){
//    case 1 : RegRequest(obj);break;
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
//    }
}

