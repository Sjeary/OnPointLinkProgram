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
    void saveKeyValue(QString key, QString value);
    void readKeyValue(QString key);
    void sendConnectRequest(QString IP, int port);
    void sendMessageToServer(QByteArray content);
    void turnLoginToWaiting();

public slots:
    void setKeyValue(QString key, QVariant value);
    void distributeMessage(QByteArray content);
    void toSendConnectRequest();
    void toSendLoginRequest(QString ID, QString password, bool rememberPassword, bool autoLogin);
    void toSendSignUpRequest(QString nickname, QString password);
    void toSendGetInfoRequest(QString ID);
    void toSendAddFriendRequest(QString ID);
    void toSendFriendResult(QString ID, bool accept);
    void toSendMessageToFriend(QString ID, QString message);


protected:
    QThread *workingThread;
    FileSystem *fileSystem;
    ClientTcp *tcp;

private:
    Login *login;
    Sign_up *sign_up;
    SwitchServerIP *switchServerIP;
    MainWindow *mainwindow;
    AddFriend *addFriend;
    DealFriendRequest *dealFriendRequest;

    QString serverIP;
    QString savedID, savedPassword;



signals:

};

#endif // CORE_H
