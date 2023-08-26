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

    ~servercore();

private slots:
    void switchFunction(QTcpSocket *psocket);
    void updateipmap(QTcpSocket *psocket);

private:
    TcpServer *tp;
    QTcpSocket *sp;
    QSqlDatabase db;
    QMap<int, QHostAddress> ipmap;
};

#endif // SERVERCORE_H
