/*
 * ============================
 * mainwindow.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 ServerCore 类
 * 在namespace Ui 当中声明 MainWindow 类
 * ============================
 *
*/

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
    void returnAccountInfoResult(bool Status, int OID, QString Name, QString Instruction, QString Emai, QDate Birth);
//    void returnFriendListResult(int OID);因为涉及动态数量，所以不编写returnresult函数，直接再request函数返回结果
    void returnUserInfoResult(bool Status, int OID, QString Name, QString Instruction, QString Emai, QDate Birth);
    void returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value);
    void SendFriendRequestToServer(QJsonObject &jsonObj);//后面五条都是以过程命名，主体都是服务器端的操作，但是名字看起来不是很像
    void ProcessFriendRequestResult(int SenderOID,int TargetOID,bool Status, QString log);
    void SendRequestToReceiverClient(int SenderOID,int TargetOID,QString RequestMessage);
    void SendResultFromReceiverClientToServer(QJsonObject &jsonObj);
    void SendResultToApplicant(int SenderOID,int TargetOID,bool Status,QString ReplyMessage);
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
