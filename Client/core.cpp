/*
 * ============================
 * clienttcp.cpp
 * 开发者：王钟骐、祝文轩、王启贤
 * Update time: 2023-8-28
 *
 * 定义 Core 类成员函数，实现核心功能
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
#include <QFile>
#include <QByteArray>
#include "front_end/login.h"
#include "front_end/sign_up.h"
#include "front_end/switchserverip.h"
#include "front_end/mainwindow.h"
#include "front_end/addfriend.h"
#include "front_end/dealfriendrequest.h"
//新增
#include "front_end/creategroup.h"

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
    //新增
    createGroup = new creategroup();

    //显示登录窗口
    QMap<QString,QString> savedAccountInfo = fileSystem->getSavedAccount();
    if (savedAccountInfo["savedOID"] != "") { // 载入记住的账号密码
        qDebug() << "load saved account" << endl;
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

    //新增
    connect(mainwindow, &MainWindow::gotoCreateGroup, createGroup, &creategroup::show);
    connect(createGroup, &creategroup::sendCreateRequest, this, &Core::toSendCreateRequest);


    connect(mainwindow, &MainWindow::sendAddFriendRequest, this, &Core::toSendAddFriendRequest);
    connect(mainwindow, &MainWindow::gotoAddFriend, addFriend, &QWidget::show);
    connect(mainwindow, &MainWindow::gotoDealFriendRequest, dealFriendRequest, &DealFriendRequest::show);
    connect(mainwindow, &MainWindow::sendMessage, this, &Core::toSendMessageToFriend);
    connect(mainwindow, &MainWindow::signal_getDocSendRequest,this,&Core::getDocSendRequest);
    connect(mainwindow, &MainWindow::sendRefreshFriendList, this, [this](){
        QJsonObject subjson;
        subjson["transType"] = "FriendListRequest";
        subjson["OID"] = this->userOID;
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
    //新增
    createGroup->deleteLater();
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
            this->userOID = json["OID"].toInt();
            login->loginSuccess();
            mainwindow->show();

            QJsonObject subjson;
            subjson["transType"] = "FriendListRequest";
            subjson["OID"] = this->userOID; // updated by zwx: 这里不用this->savedOID，那个在没有勾选“保存密码”时为空。
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
        QString senderOID = QString::number(json["OID1"].toInt());
        mainwindow->getFriendRequest();
        dealFriendRequest->addRequestItem(senderOID,"");
    }
    else if(transType == "SendMessageRequest")
    /*
     * 收到一条消息
    */
    {
        // p2p消息（文本、文件）
        QString senderOID = json["senderOID"].toString();
        QString targetOID = json["targetOID"].toString();
        if(targetOID.toInt() == this->userOID) {
            QString name = mainwindow->getNameByOID(senderOID);
            if(json["Type"].toString() == "Document") {
                QString filename = json["Value"].toString();
                mainwindow->addDocMessage(senderOID,name,filename,true);
                QString savePath("./Files/");
                savePath += senderOID + QString("/") + targetOID + QString("/");
                this->writeDocFromByteArray(savePath,filename,json["Content"].toString());
            }
            else if(json["Type"] == "Txt")mainwindow->addMessage(senderOID,name,json["Value"].toString(),true);
        }
        else // 群发文件
        {
            qDebug() << "群文件发送功能还未完成" << endl;
            return;
        }
    }
    else if(transType == "FriendListResult")
    {
        mainwindow->clearFriendItem();
        mainwindow->clearMessageItem();
        QJsonArray friendList = json["FriendList"].toArray();
        foreach (auto var, friendList) {
            QJsonObject f = var.toObject();
            QString ID = QString::number(f["FriendOID"].toInt());
            QString name = f["FriendName"].toString();
            mainwindow->addFriendItem(ID, name);
            mainwindow->addMessageItem(ID, name);
            //新增
            createGroup->addFriendItem(ID, "");

            qDebug()<<ID;
        }
    }
    else if (transType == "SendMessageResult")
    {
        QString SenderOID = QString::number(json["SenderOID"].toInt());
        QString TargetOID = QString::number(json["TargetOID"].toInt());
        QString Value = json["Value"].toString();
        qDebug() << "SendMessageResult: " << json << endl;
        if(json["transType"] == "Txt")mainwindow->addMessage(SenderOID, "", Value, true);
//        else if(json["transType"] == "Document") mainwindow -> addDocMessage(SenderOID, "", TargetOID, Value);
    }
    //新增
    else if (transType == "CreateGroupResult")
    {
        bool success = json["Status"].toBool();
        QString GroupID = QString::number(json["GroupID"].toInt());
        QString HostOID = QString::number(json["HostOID"].toInt());
        QString memberOIDs = json["memberOIDs"].toString();
        if (success)
        {
            QMessageBox::information(mainwindow, "group created", "Your created group's OID is " + GroupID );
        }
        else
        {
            QMessageBox::information(mainwindow, "creation failed", "Failed!" );
        }
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
        fileSystem->toSaveKeyValue("savedOID",ID.toInt());
        fileSystem->toSaveKeyValue("savedPassword",password);
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
    json["SenderOID"] = userOID; // updated by zwx: 别用savedID，这玩意儿是用来存下次登录的账号的，易篡改
    json["TargetOID"] = ID.toInt();
    json["Type"] = "Txt";
    json["Value"] = message;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}

//新增
void Core::toSendCreateRequest(QStringList memberIDList)
{
    QJsonObject json;
    QJsonArray jsonArray;
    foreach (const QString &memberID, memberIDList)
    {
        jsonArray.append(memberID);
    }
    json["transType"] = "SendCreateGroupRequest";
    json["HostOID"] = savedID.toInt();
    json["memberOIDs"] = jsonArray;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}

QString getName(const QString &path)
{
    QString str1 = path.section('/',-1);
    return str1;
}

void Core::getDocSendRequest(QString targetOID,QString path)
/*
 * getDocSendRequest
 * 从mainwindow收到文件消息的信息，将其发送
 * updated by zwx.
*/
{
    QFile file = QFile(path);
    if (! file.open(QIODevice::ReadOnly)) {
        QMessageBox msgbox;
        msgbox.setParent(mainwindow);
        msgbox.setText(QString("无法读取该文件：\n%1").arg(path));
        msgbox.exec();
        return;
    }
    QByteArray content = file.readAll();
    this->toSendDocuMessage(targetOID,content,getName(path));
}

void Core::toSendDocuMessage(const QString targetOID,const QByteArray content,const QString filename)
{
    QJsonObject job;
    job["transType"] = "SendMessageRequest";
    job["Type"] = "Document";
    job["SenderOID"] = QString::number(this->userOID);
    job["TargetOID"] = targetOID;
    job["Value"] = filename;
    job["Content"] = QString(content.toBase64());
    QJsonDocument jdoc(job);
    tcp->toSendMessage(jdoc.toJson());
}

void Core::toSendDocuMessageBypath(const QString targetOID,const QString path)
{
    QFile file(path);
    if (! file.open(QIODevice::ReadOnly)) {
        QMessageBox msgbox;
        msgbox.setParent(mainwindow);
        msgbox.setText(QString("无法读取该文件：\n%1").arg(path));
        msgbox.exec();
        return;
    }
    QByteArray content = file.readAll();
    this->toSendDocuMessage(targetOID,content,getName(path));
}

void Core::writeDocFromByteArray(QString path,QString filename,QString content_base53String)
{
    QFile file(path+filename);
    if(! file.open(QIODevice::WriteOnly)) {
        qDebug() << "Core.writeDocFromByteArray Error！" << filename << endl;
        return;
    }
    QByteArray array = QByteArray::fromBase64(content_base53String.toUtf8());
    file.write(array);
    file.close();
}
