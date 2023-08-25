#include "core.h"

#include <QThread>
#include "front_end/login.h"
#include "front_end/sign_up.h"
#include "front_end/switchserverip.h"
#include "front_end/mainwindow.h"
#include "front_end/addfriend.h"
#include "front_end/dealfriendrequest.h"
#include "rear_end/filesystem.h"
#include "rear_end/clienttcp.h"


Core::Core(QObject *parent)
    : QObject{parent}
{
    //start working thread
    workingThread = new QThread;
    fileSystem = new FileSystem;
    tcp = new ClientTcp;
    fileSystem->moveToThread(workingThread);
    tcp->moveToThread(workingThread);

    workingThread->start();

    //build each windows
    login = new Login();
    sign_up = new Sign_up();
    switchServerIP = new SwitchServerIP();
    mainwindow = new MainWindow();
    addFriend = new AddFriend();
    dealFriendRequest = new DealFriendRequest();
    //show login window
    login->show();
    switchServerIP->show();

    mainwindow->addMessageItem("000", "me");
    dealFriendRequest->addRequestItem("000","me");

    //connections

    connect(this, &Core::start, fileSystem, &FileSystem::makeBasicFolder);
    connect(this, &Core::sendConnectRequest, tcp, &ClientTcp::tryConnect);
    connect(this, &Core::sendMessageToServer, tcp, &ClientTcp::toSendMessage);

    connect(tcp, &ClientTcp::getConnect, login, &Login::connectedToServer);
    connect(tcp, &ClientTcp::connectFailed, login, &Login::cannotConnect);
    connect(tcp, &ClientTcp::getMessage, this, [this](QByteArray content){
        qDebug()<<content;
    });

    connect(login, &Login::reconnectToServer, this, [this](){
        emit this->sendConnectRequest(serverIP, 6666);
    });
    connect(login, &Login::sendLogin, this, [this](QString ID, QString password, bool rememberPassword, bool autoLogin){
        emit this->sendMessageToServer(QString("ID:"+ID+". password:"+password+". try to login").toUtf8());
    });
    connect(login, &Login::gotoSignUp, sign_up, &QWidget::show);
    connect(login, &Login::gotoSwitchServerIP, switchServerIP, &QWidget::show);

    connect(switchServerIP, &SwitchServerIP::sendNewIP, this, [this](QString newIP){
        this->serverIP = newIP;
    });

    connect(mainwindow, &MainWindow::gotoAddFriend, addFriend, &QWidget::show);
    connect(mainwindow, &MainWindow::gotoDealFriendRequest, dealFriendRequest, &DealFriendRequest::show);

    emit start();

}

Core::~Core()
{
    //cut down working thread
    workingThread->quit();
    workingThread->wait();
    workingThread->deleteLater();

    fileSystem->deleteLater();
    tcp->deleteLater();

    //delete windows
    login->deleteLater();
    sign_up->deleteLater();
    switchServerIP->deleteLater();
    mainwindow->deleteLater();
    addFriend->deleteLater();
    dealFriendRequest->deleteLater();
}
