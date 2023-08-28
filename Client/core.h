/*
 * ============================
 * core.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 Core 类。
 * 声明 Core 类的成员函数。
 * ============================
 *
*/

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread> // updated by zwx.
#include <QMap>
#include <QVariant>

#include <QJsonDocument>

class QThread;

class Login;
class Sign_up;
class SwitchServerIP;
class MainWindow;
class AddFriend;
class FileSystem;
class DealFriendRequest;
class ClientTcp;

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

signals:
    //保存键值对信息到本地
    void saveKeyValue(QString key, QString value);
    //读取本地存储的键值对信息
    void readKeyValue(QString key);
    //发送链接到服务器的信号
    void sendConnectRequest(QString IP, int port);
    //发送信息到服务器（一个.json文件）
    void sendMessageToServer(QByteArray content);
    
    void turnLoginToWaiting();

public slots:
    //得到本地存储的键值对
    void setKeyValue(QString key, QVariant value);
    //分发服务器发来的各种信息
    void distributeMessage(QByteArray content);
    //处理前端发来的链接到服务器请求
    void toSendConnectRequest();
    //处理前端发来的登录请求
    void toSendLoginRequest(QString ID, QString password, bool rememberPassword, bool autoLogin);
    //处理前端发来的注册请求
    void toSendSignUpRequest(QString nickname, QString password);
    //处理前端发来的获得用户信息请求
    void toSendGetInfoRequest(QString ID);
    //处理前端发来的添加好友请求
    void toSendAddFriendRequest(QString ID);
    //处理前端发来的接受/拒绝好友申请的请求
    void toSendFriendResult(QString ID, bool accept);
    //处理前端发来的给好友发送消息请求
    void toSendMessageToFriend(QString ID, QString message);

    //文件消息发送的几个函数
    void getDocSendRequest(QString targetOID,QString path); // updated by zwx.
    void toSendDocuMessage(const QString targetOID,const QByteArray content,const QString filename); // updated by zwx.
    void toSendDocuMessageBypath(const QString targetOID,const QString path); // updated by zwx.
    void openChooseFileDialog(const QString targetOID); // updated by zwx.

protected:
    //后台工作线程
    QThread *workingThread;
    //本地文件处理类
    FileSystem *fileSystem;
    //网络链接类
    ClientTcp *tcp;

private:
    //一些窗口
    Login *login;
    Sign_up *sign_up;
    SwitchServerIP *switchServerIP;
    MainWindow *mainwindow;
    AddFriend *addFriend;
    DealFriendRequest *dealFriendRequest;

    //暂存在内存的服务器IP地址
    QString serverIP;
    //暂存在内存的当前登录用户OID和密码
    QString savedID, savedPassword;
    int userOID;

};

#endif // CORE_H
