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

#ifdef _WIN32
#include <Windows.h>

#elif __linux__
#include <unistd.h>

#endif



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
    void returnSendTextMessageResult(bool Status, int MID, int SenderOID, int TargetOID, QString Type, QString Value,QString SenderName,QString Content);
    void SendFriendRequestToServer(QJsonObject &jsonObj);//后面五条都是以过程命名，主体都是服务器端的操作，但是名字看起来不是很像
    void ProcessFriendRequestResult(int SenderOID,int TargetOID,bool Status, QString log);
    void StoreOfflineFriendRequest(int SenderOID, int TargetOID, QString ApplicationMessage);
    void SendRequestToReceiverClient(int SenderOID,int TargetOID,QString RequestMessage);
    void SendResultFromReceiverClientToServer(QJsonObject &jsonObj);
    void SendResultToApplicant(int SenderOID,int TargetOID,bool Status,QString ReplyMessage);

    //同步服务器离线消息到客户端
    void SynchronizeServerMessages(int OID1);
    //删好友，改分组
    void SendCreateGroupRequest(QJsonObject &);
    void SendDeleteFriendRequest(QJsonObject &jsonObj);
    void returnSendDeleteFriendRequest(int OID1,int OID2,bool Status,QString log,QString Devide,QString transType);
    void ChangeFriendDevide(QJsonObject &jsonObj);
    void returnChangeFriendDevide(int OID1,int OID2,bool Status,QString log,QString transType);
    //群聊消息
    void SendGroupMessage(QJsonObject &jsonObj);
    void returnSendGroupMessage(bool Status,QString log,int GroupOID,int SenderMemberOID,QString Content,QString Type,QString transType);

    ~servercore();

private slots:
    void switchFunction(QTcpSocket *psocket);
    void offline(QTcpSocket *psocket);

private:
    TcpServer *tp; // 服务器的指针
    QTcpSocket *sp; // 套接字的指针
    QSqlDatabase db; // 数据库对象
    quint16 defalutport = 6666; // 默认端口
    QString filepath = "C:/Users/sjr12/Desktop/OnPointLink/"; // 文件存放位置
    QMap<int, QTcpSocket *> socketmap; // 上线OID到ip的map
};

#endif // SERVERCORE_H
