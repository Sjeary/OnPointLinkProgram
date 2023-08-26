#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QDebug>
#include <QSqlError>
#include <QtSql>
#include <QJsonDocument>
#include <QByteArray>
#include <QMap>
#include "tcpserver.h"

class servercore : public QObject
{
    Q_OBJECT
public:
    explicit servercore(TcpServer *ptcpserver, QObject *parent = nullptr);
    void RegRequest(QJsonObject &jsonData);
    void EnterRequest(QJsonObject &);
    void AccountInfoRequest(QJsonObject &);
    void FriendListRequest(QJsonObject &);
    void GroupListRequest(QJsonObject &);
    void UserInfoRequest(QJsonObject &);
    void GroupInfoRequest(QJsonObject &);
    void SendTxtMessageRequest(QJsonObject &);
    void TargetMessageRequest(QJsonObject &);
    void MessageReadedRequest(QJsonObject &);
    void FileListRequest(QJsonObject &);
    void FileRequest(QJsonObject &);


    void returnRegResult(int OID,bool Status,QString log,QString Name);
    void returnEnterResult(int OID, QHostAddress ip, bool status, QString log);
    void returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value);

    ~servercore();

private slots:
    void switchFunction(QTcpSocket *psocket);
    void offline(QTcpSocket *psocket);

private:
    TcpServer *tp; // 服务器的指针
    QTcpSocket *sp; // 套接字的指针
    QSqlDatabase db; // 数据库对象
    quint16 defalutport = 6666; // 默认端口
    QMap<int, QHostAddress> ipmap; // 上线OID到ip的map
};

#endif // SERVERCORE_H
