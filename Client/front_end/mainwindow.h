/*
 * ============================
 * mainwindow.h
 * 开发者：王钟骐、祝文轩、王启贤
 * Update time: 2023-8-27
 *
 * 定义 MainWindow 类
 * 声明 MainWindow 类的成员函数
 * ============================
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMap>
#include "accountsettings.h"

class QTextDocument;
class QListWidgetItem;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



signals:
    void sendMessage(QString ID, QString content);
    void sendAddFriendRequest(QString ID);
    void sendRefreshFriendList();

    void gotoAddFriend();
    void gotoDealFriendRequest();
    //新增
    void gotoCreateGroup();

public slots:
    //获得好友发来的消息
    void getMessage(QString ID, QString name, QString content, bool isReceive);
    //获得查询到的用户信息
    void getUserInfo(QString ID, QString name, QString ins, QString email, QString birth);
    //接受到好友申请
    void getFriendRequest();
    //消息窗口添加一个项目
    void addMessageItem(QString ID, QString name);
    //好友窗口添加一个项目
    void addFriendItem(QString ID, QString name);
    //改变消息窗口当前项目
    void changeMessageItem(QListWidgetItem *current);
    //清除消息窗口所有项目
    void clearMessageItem();
    //清除好友窗口所有项目
    void clearFriendItem();
    //新增
    //void getGroupInfo(QString ID, QString name, QString ins, QString memberIDs);

private slots:
    void on_pushButton_input_clicked();

    void on_radioButton_message_toggled(bool checked);

    void on_radioButton_friends_toggled(bool checked);

    void on_radioButton_settings_toggled(bool checked);

    void on_pushButton_addFriend_clicked();

    void on_pushButton_friendRequest_clicked();

    void on_pushButton_addThisUser_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_createGroup_clicked();

private:
    Ui::MainWindow *ui;

    QMap<QListWidgetItem*, QTextDocument*> documents;
    QMap<QTextDocument*, int> documentToOID;
    AccountSettings *acSetting; // 设置界面的Widget

    void setRootFrameFormat(QTextDocument *doc);

    void insertLeftFrame(QTextDocument *doc, const QString &title, const QString &text);

    void insertRightFrame(QTextDocument *doc, const QString &title,const QString &text);
};

#endif // MAINWINDOW_H
