#include "core.h"

#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

    mainwindow->addMessageItem("000", "me 0");
    mainwindow->addMessageItem("001", "me 1");
    mainwindow->addMessageItem("002", "me 2");

    dealFriendRequest->addRequestItem("000","me");

    //connections

    connect(this, &Core::sendConnectRequest, tcp, &ClientTcp::tryConnect);
    connect(this, &Core::sendMessageToServer, tcp, &ClientTcp::toSendMessage);
    connect(this, &Core::saveKeyValue, fileSystem, &FileSystem::toSaveKeyValue);
    connect(this, &Core::readKeyValue, fileSystem, &FileSystem::toReadKeyValue);

    connect(fileSystem, &FileSystem::getKeyValue, this, &Core::getKeyValue);

    connect(tcp, &ClientTcp::getConnect, login, &Login::connectedToServer);
    connect(tcp, &ClientTcp::connectFailed, login, &Login::cannotConnect);
    connect(tcp, &ClientTcp::getMessage, this, &Core::distributeMessage);

    connect(switchServerIP, &SwitchServerIP::sendNewIP, this, [this](QString newIP){
        this->serverIP = newIP;
    });


    connect(login, &Login::reconnectToServer, this, &Core::toSendConnectRequest);
    connect(login, &Login::sendLogin, this, &Core::toSendLoginRequest);

    connect(login, &Login::gotoSignUp, sign_up, &QWidget::show);
    connect(login, &Login::gotoSwitchServerIP, switchServerIP, &QWidget::show);

    connect(sign_up, &Sign_up::sendSignUp, this, &Core::toSendSignUpRequest);

    connect(addFriend, &AddFriend::GetInfo, this, &Core::toSendGetInfoRequest);


    connect(mainwindow, &MainWindow::gotoAddFriend, addFriend, &QWidget::show);
    connect(mainwindow, &MainWindow::gotoDealFriendRequest, dealFriendRequest, &DealFriendRequest::show);

    emit readKeyValue("serverIP");
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

void Core::getKeyValue(QString key, QString value)
{
    qDebug()<<"read"<<value;
    if (key == "serverIP")
    {
        serverIP = value;
        if(not serverIP.isEmpty())
        {
            toSendConnectRequest();
        }
    }
}

void Core::distributeMessage(QByteArray content)
{
    QJsonDocument doc = QJsonDocument::fromJson(content);
    if(doc.isNull() or not doc.isObject())
    {
        return;
    }
    QJsonObject json = doc.object();
    QString transType = json["transType"].toString();

    if(transType == "EnterResult")
    {
        bool success = json["Status"].toBool();
        if(success)
        {
            login->loginSuccess();
            mainwindow->show();
        }
        else
        {
            login->loginFailed(json["log"].toString());
        }
    }
    else if(transType == "RegResult")
    {
        bool success = json["Status"].toBool();
        if(success)
        {
            sign_up->signUpSuccess(QString::number(json["OID"].toInt()));
        }
        else
        {
            sign_up->signUpFailed(json["log"].toString());
        }
    }
    else if(transType == "AccountInfoResult")
    {
        bool success = json["Status"].toBool();
        if(success)
        {
            QString ID = json["OID"].toString();
            QString name = json["Name"].toString();
            QString ins = json["Instruction"].toString();
            QString email = json["Email"].toString();
            QString birth = json["Birth"].toString();
            mainwindow->getUserInfo(ID, name, ins, email, birth);
        }
    }
}

void Core::toSendConnectRequest()
{
    emit this->sendConnectRequest(serverIP, 6666);
    emit saveKeyValue("serverIP", serverIP);
}

void Core::toSendLoginRequest(QString ID, QString password, bool rememberPassword, bool autoLogin)
{
    QJsonObject json;
    json["transType"] = "EnterRequest";
    json["OID"] = ID.toInt();
    json["Password"] = password;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
    savedID = ID;
    if(rememberPassword)
    {
        savedPassword = password;
    }
    if(autoLogin)
    {

    }
}
void Core::toSendSignUpRequest(QString nickname, QString password)
{
    QJsonObject json;
    json["transType"] = "RegRequest";
    json["Name"] = nickname;
    json["Password"] = password;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}
void Core::toSendGetInfoRequest(QString ID)
{
    QJsonObject json;
    json["transType"] = "AccountInfoRequest";
    json["OID"] = ID.toInt();
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}
