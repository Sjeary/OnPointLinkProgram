/*
 * ============================
 * clienttcp.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 Core 类成员函数
 * ============================
 *
*/

#include "core.h"

#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>
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
    /*
     * Core类构造函数。
     * 建立各个功能窗口、后台线程、槽连接
    */
{
    //start working thread
    workingThread = new QThread;
    fileSystem = new FileSystem;
    tcp = new ClientTcp;
    fileSystem->moveToThread(workingThread);
    tcp->moveToThread(workingThread);

    workingThread->start();

    //建立各个功能窗口
    login = new Login();
    sign_up = new Sign_up();
    switchServerIP = new SwitchServerIP(nullptr,fileSystem->getSavedServerIP());
    mainwindow = new MainWindow();
    addFriend = new AddFriend();
    dealFriendRequest = new DealFriendRequest();
    //显示登录窗口
    QMap<QString,QString> savedAccountInfo = fileSystem->getSavedAccount();
    if (savedAccountInfo["savedOID"] == "") { // 载入记住的账号密码
        login->writeSavedAccountInfo(savedAccountInfo["savedOID"],savedAccountInfo["savedPassword"]);
    }
    login->show();

    //connections

    connect(this, &Core::sendConnectRequest, tcp, &ClientTcp::tryConnect);
    connect(this, &Core::sendMessageToServer, tcp, &ClientTcp::toSendMessage);
    connect(this, &Core::saveKeyValue, fileSystem, &FileSystem::toSaveKeyValue);
    connect(this, &Core::readKeyValue, fileSystem, &FileSystem::toReadKeyValue);

    connect(fileSystem, &FileSystem::setCoreKeyValue, this, &Core::setKeyValue);

    connect(tcp, &ClientTcp::getConnect, login, &Login::connectedToServer);
    connect(tcp, &ClientTcp::connectFailed, login, &Login::cannotConnect);
    connect(tcp, &ClientTcp::getMessage, this, &Core::distributeMessage);

    connect(switchServerIP, &SwitchServerIP::sendNewIP, this, [this](QString newIP){
        this->serverIP = newIP;
        fileSystem->toSaveKeyValue("serverIP",newIP);
    });


    connect(login, &Login::reconnectToServer, this, &Core::toSendConnectRequest);
    connect(login, &Login::sendLogin, this, &Core::toSendLoginRequest);
    connect(this,&Core::turnLoginToWaiting,login,&Login::turnToWaiting);
    connect(login, &Login::gotoSignUp, sign_up, &QWidget::show);
    connect(login, &Login::gotoSwitchServerIP, switchServerIP, &QWidget::show);
    // /*temp*/connect(login, &Login::sendLogin, mainwindow, &MainWindow::show);

    connect(sign_up, &Sign_up::sendSignUp, this, &Core::toSendSignUpRequest);

    connect(addFriend, &AddFriend::getInfo, this, &Core::toSendGetInfoRequest);
    connect(dealFriendRequest, &DealFriendRequest::dealFriendRequest, this, &Core::toSendFriendResult);

    connect(mainwindow, &MainWindow::sendAddFriendRequest, this, &Core::toSendAddFriendRequest);
    connect(mainwindow, &MainWindow::gotoAddFriend, addFriend, &QWidget::show);
    connect(mainwindow, &MainWindow::gotoDealFriendRequest, dealFriendRequest, &DealFriendRequest::show);
    connect(mainwindow, &MainWindow::sendMessage, this, &Core::toSendMessageToFriend);
    connect(mainwindow, &MainWindow::sendRefreshFriendList, this, [this](){
        QJsonObject subjson;
        subjson["transType"] = "FriendListRequest";
        subjson["OID"] = savedID.toInt();
        QJsonDocument subdoc(subjson);
        emit this->sendMessageToServer(subdoc.toJson());
    });

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

void Core::setKeyValue(QString key, QVariant value)
/*
 * setKeyValue
 * 功能：设置core对象中，key值对应的变量的值。
 * 参数说明：
 * key: 参数名字，可选项："serverIP"。
 * value: 设置值
*/
{
    qDebug()<<"Core: getKeyValue: key: "<<key<<" value: "<<value;
    if (key == "serverIP")
    {
        serverIP = value.toString();
        if(! serverIP.isEmpty())
        {
            toSendConnectRequest();
        }
        else{
            qDebug() << "core: Empty server IP!";
        }
    }
}

void Core::distributeMessage(QByteArray content)
/*
 * distributeMessage
 * 功能：在接收到服务器的信息content后，
 *    读取content存储的.json文件二进制流，
 *    根据content["transType"]属性来判断类型。
 * 参数：content，必须为一个能转为.json文件的二进制流。
*/
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

            QJsonObject subjson;
            subjson["transType"] = "FriendListRequest";
            subjson["OID"] = savedID.toInt();
            QJsonDocument subdoc(subjson);
            emit this->sendMessageToServer(subdoc.toJson());
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
            QString ID = QString::number(json["OID"].toInt());
            QString name = json["Name"].toString();
            QString ins = json["Instruction"].toString();
            QString email = json["Email"].toString();
            QString birth = json["Birth"].toString();
            mainwindow->getUserInfo(ID, name, ins, email, birth);
            addFriend->hide();
        }
        else
        {
            addFriend->getInfoFailed();
        }
    }
    else if(transType == "ProcessFriendRequestResult")
    {
        bool success = json["Status"].toBool();
        QString targetOID = json["OID2"].toString();
        if(success)
        {
            QMessageBox::information(mainwindow, "request sent", "Your add friend request to " + targetOID + " has been sent");
        }
        else
        {
            QMessageBox::warning(mainwindow, "request failed", "Your add friend request to " + targetOID + " cannot send");
        }
    }
    else if(transType == "SendRequestToReceiverClient")
    {
        QString senderOID = json["OID1"].toString();
        mainwindow->getFriendRequest();
        dealFriendRequest->addRequestItem(senderOID,"");
    }
    else if(transType == "FriendListResult")
    {
        QJsonArray friendList = json["FriendList"].toArray();
        foreach (auto var, friendList) {
            QJsonObject f = var.toObject();
            QString ID = f["FriendOID"].toString();
            mainwindow->addFriendItem(ID, "");
            mainwindow->addMessageItem(ID, "");
            qDebug()<<ID;
        }
    }
    else if (transType == "TargetMessageRequest")
    {
        QString SenderOID = QString::number(json["SenderOID"].toInt());
        QString TargetOID = QString::number(json["TargetOID"].toInt());
        QString Value = json["Value"].toString();
        mainwindow->getMessage(TargetOID, "", Value, true);
    }
}

void Core::toSendConnectRequest()
{
    emit this->sendConnectRequest(serverIP, 6666);
    emit saveKeyValue("serverIP", serverIP);
}

void Core::toSendLoginRequest(QString ID, QString password, bool rememberPassword, bool autoLogin)
/*
 * toSendLoginRequest
 * slot函数，接收信号：login.sendLogin
 * 功能：向服务器发送.json信息文件，并且根据
 * rememberPassword参数保存密码。
 * 参数：
 * ID：登录者的OID
 * password；登录者输入的密码
 * rememberPassword： bool类型，表示是否保存密码
 * autoLogin：下次是否自动登录（目前没有用上）
*/
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
        fileSystem->toSaveKeyValue("savedOID",savedID);
        fileSystem->toSaveKeyValue("savedPassword",savedPassword);
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

void Core::toSendAddFriendRequest(QString ID)
{
    QJsonObject json;
    json["transType"] = "SendFriendRequestToServer";
    json["OID1"] = savedID.toInt();
    json["OID2"] = ID.toInt();
    json["RequestMessage"] = "hello";
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}

void Core::toSendFriendResult(QString ID, bool accept)
{
    QJsonObject json;
    json["transType"] = "SendResultFromReceiverClientToServer";
    json["OID1"] = ID.toInt();
    json["OID2"] = savedID.toInt();
    json["ReplyMessage"] = "hello";
    json["Accepted"] = accept;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}

void Core::toSendMessageToFriend(QString ID, QString message)
{
    QJsonObject json;
    json["transType"] = "SendTxtMessageRequest";
    json["SenderOID"] = savedID.toInt();
    json["TargetOID"] = ID.toInt();
    json["Value"] = message;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}
