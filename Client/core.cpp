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
#include "front_end/changegroup.h"
#include "front_end/newtempgroup.h"
#include "front_end/choosedocdialog.h"
#include <unistd.h>

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
    changeGroup = new ChangeGroup();
    newTempGroup = new NewTempGroup();

    //显示登录窗口
    QMap<QString,QString> savedAccountInfo = fileSystem->getSavedAccount();
    if (savedAccountInfo["savedOID"] != "") { // 载入记住的账号密码
        qDebug() << "load saved account" ;
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
    connect(mainwindow, &MainWindow::getInfo, this, &Core::toSendGetInfoRequest);
    connect(mainwindow, &MainWindow::gotoDeleteFriend, this, &Core::toSendDeleteFriendRequest);
    connect(mainwindow, &MainWindow::gotoBlockFriend, this, &Core::toSendChangeGroupRequest);
    connect(mainwindow, &MainWindow::gotoChangeGroup, changeGroup, &ChangeGroup::show);
    connect(mainwindow, &MainWindow::giveOID, changeGroup, &ChangeGroup::receiveID);
    connect(changeGroup, &ChangeGroup::sendChangeGroup, this, &Core::toSendChangeGroupRequest);
    connect(changeGroup, &ChangeGroup::gotoNewGroup, newTempGroup, &NewTempGroup::show);
    connect(newTempGroup, &NewTempGroup::giveNewGroupName, changeGroup, &ChangeGroup::newGroupName);


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
        usleep(200000);

        QJsonObject subjson1;
        subjson1["transType"] = "GetGroupChatList";
        subjson1["OID"] = this->userOID;
        QJsonDocument subdoc1(subjson1);
        emit this->sendMessageToServer(subdoc1.toJson());
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
    changeGroup->deleteLater();
    newTempGroup->deleteLater();
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
            usleep(200000);
            QJsonObject subjson1;
            subjson1["transType"] = "GetGroupChatList";
            subjson1["OID"] = this->userOID;
            QJsonDocument subdoc1(subjson1);
            emit this->sendMessageToServer(subdoc1.toJson());
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
    //新增
    else if(transType == "GroupInfoResult")
    {
        bool success = json["Status"].toBool();
        if(success)
        {
            QString GroupID = QString::number(json["OID"].toInt());
            QString HostOID = json["Name"].toString();
            QString memberIDs = json["MembersOIDs"].toString();
            mainwindow->getGroupInfo(GroupID, HostOID, memberIDs);
        }
        else
        {
            QMessageBox::information(mainwindow, "search failed", "Failed!" );
        }
    }
    //
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
            qDebug() << "群文件发送功能还未完成" ;
            return;
        }
    }
    else if(transType == "FriendListResult")
    {
        mainwindow->clearFriendItem();
        mainwindow->clearMessageItem();
        createGroup->clearCreateGroupItem();
        changeGroup->clearChangeGroupItem();

        QJsonArray friendList = json["FriendList"].toArray();
        foreach (auto var, friendList) {
            QJsonObject f = var.toObject();
            QString ID = QString::number(f["FriendOID"].toInt());
            QString name = f["FriendName"].toString();
            QString groupname = f["Devide"].toString();
            mainwindow->addFriendItem(ID, name, groupname);
            mainwindow->addMessageItem(ID, name);
            //新增
            createGroup->addFriendItem(ID, "no");
            changeGroup->addGroupItem(groupname, "no");

            qDebug()<<ID;
        }
    }
    //新增
    else if(transType == "returnGetGroupChatList")
    {

        QJsonArray groupList = json["Group"].toArray();
        foreach (auto var, groupList) {
            QJsonObject f = var.toObject();
            QString ID = QString::number(f["GroupOID"].toInt());
            //QString name = f["FriendName"].toString();
            QString groupname = "群聊";
            mainwindow->addFriendItem(ID, "", groupname);
            mainwindow->addMessageItem(ID, "群聊");
            //新增

            qDebug()<<ID;
        }
    }
    //
    else if (transType == "SendMessageResult")
    {
        QString SenderOID = QString::number(json["SenderOID"].toInt());
        QString TargetOID = QString::number(json["TargetOID"].toInt());
        QString Value = json["Value"].toString();
        bool status = json["Status"].toBool();
        qDebug() << "SendMessageResult: " << json ;
        if(SenderOID == savedID)return;
        if(json["Type"] == "Txt")mainwindow->addMessage(SenderOID, "", Value, true);
        else if(json["transType"] == "Document") {
            if(status)
                mainwindow -> addDocMessage(SenderOID, "", Value, true);
            else
                mainwindow -> addDocMessage(SenderOID, "", "（发送失败）"+Value, true);
        }
    }
    else if (transType == "SendGroupMessage")
    {
        QString SenderMemberOID = QString::number(json["SenderMemberOID"].toInt());
        QString GroupOID = QString::number(json["GroupOID"].toInt());
        QString Content = json["Content"].toString();
        if(SenderMemberOID == savedID)return;
        qDebug() << "SendMessageResult: " << json << endl;
        if(json["Type"] == "Txt")mainwindow->addMessage(GroupOID, SenderMemberOID, Content, true);
//        else if(json["transType"] == "Document") mainwindow -> addDocMessage(SenderOID, "", TargetOID, Value);
    }
    //新增
    else if (transType == "CreateGroupResult")
    {
        int success = json["Status"].toInt();
        QString GroupID = QString::number(json["GroupOID"].toInt());
        //QString HostOID = QString::number(json["HostOID"].toInt());
        //QString memberOIDs = json["memberOIDs"].toString();
        if (success)
        {
            mainwindow->addFriendItem(GroupID, "", "群聊");
            mainwindow->addMessageItem(GroupID, "群聊");
            QMessageBox::information(mainwindow, "group created", "Your created group's OID is " + GroupID );
        }
        else
        {
            QMessageBox::information(mainwindow, "creation failed", "Failed!" );
        }
    }
    else if (transType == "DeleteFriendResult")
    {
        bool success = json["Status"].toBool();
        QString ID = QString::number(json["ID"].toInt());
        if (success)
        {
            QMessageBox::information(mainwindow, "success", "删除成功" );
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
    if(ID.length() == 5)
    {
        QJsonObject json;
        json["transType"] = "AccountInfoRequest";
        json["OID"] = ID.toInt();
        QJsonDocument doc(json);
        emit this->sendMessageToServer(doc.toJson());
    }
    else if(ID.length() == 6)
    {
        QJsonObject json;
        json["transType"] = "GroupInfoRequest";
        json["OID"] = ID.toInt();
        QJsonDocument doc(json);
        emit this->sendMessageToServer(doc.toJson());
    }
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
    if(ID.length() == 5)
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
    else if(ID.length() == 6)
    {
        QJsonObject json;
        json["transType"] = "SendGroupMessage";
        json["SenderMemberOID"] = userOID; // updated by zwx: 别用savedID，这玩意儿是用来存下次登录的账号的，易篡改
        json["GroupOID"] = ID.toInt();
        json["Type"] = "Txt";
        json["Content"] = message;
        QJsonDocument doc(json);
        emit this->sendMessageToServer(doc.toJson());
    }
}

//新增
void Core::toSendCreateRequest(QStringList memberIDList)
{
    QJsonObject json;
    QJsonArray jsonArray;
    foreach (const QString &memberID, memberIDList)
    {
        QJsonObject obj;
        obj["OID"] = memberID.toInt();
        jsonArray.append(obj);
    }
    json["transType"] = "SendCreateGroupRequest";
    json["HostOID"] = savedID.toInt();
    json["memberOID"] = jsonArray;
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
    job["SenderOID"] = this->userOID;
    job["TargetOID"] = targetOID.toInt();
    job["Value"] = filename;
    job["Content"] = QString(content.toBase64());
    QJsonDocument jdoc(job);
    emit this->sendMessageToServer(jdoc.toJson());
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
        qDebug() << "Core.writeDocFromByteArray Error！" << filename ;
        return;
    }
    QByteArray array = QByteArray::fromBase64(content_base53String.toUtf8());
    file.write(array);
    file.close();
}

void Core::toSendDeleteFriendRequest(QString ID)
{
    QJsonObject json;
    json["transType"] = "SendDeleteFriendRequest";
    json["OID1"] = savedID.toInt();
    json["OID2"] = ID.toInt();
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}

void Core::toSendChangeGroupRequest(QString ID, QString groupname)
{
    QJsonObject json;
    json["transType"] = "ChangeFriendDevide";
    json["OID1"] = savedID.toInt();
    json["OID2"] = ID.toInt();
    json["Devide"] = groupname;
    QJsonDocument doc(json);
    emit this->sendMessageToServer(doc.toJson());
}
