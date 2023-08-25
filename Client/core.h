#ifndef CORE_H
#define CORE_H

#include <QObject>

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

    void toSendLoginRequest();
    void toSendSignUpRequest();
    void toSendGetInfoRequest();

    void getLoginResult();
    void getSignUpResult();
    void getUerInfoResult();

signals:
    void start();
    void sendConnectRequest(QString IP, int port);
    void sendMessageToServer(QByteArray content);

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

signals:

};

#endif // CORE_H
