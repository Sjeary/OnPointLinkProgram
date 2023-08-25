#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include "tcpserver.h"

class servercore : public QObject
{
    Q_OBJECT
public:
    explicit servercore(TcpServer *ptcpserver, QObject *parent = nullptr);
    void RegRequest(QJsonObject &);
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

private slots:
    void switchFunction(QTcpSocket *psocket);

private:
    TcpServer *tp;
};

#endif // SERVERCORE_H
