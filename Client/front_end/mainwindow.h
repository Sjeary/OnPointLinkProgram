/*
 * ============================
 * mainwindow.h
 * 开发者：希望之花团队
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

public slots:
    void getMessage(QString ID, QString name, QString content, bool isReceive);
    void getUserInfo(QString ID, QString name, QString ins, QString email, QString birth);
    void getFriendRequest();
    void addMessageItem(QString ID, QString name);
    void addFriendItem(QString ID, QString name);

    void changeMessageItem(QListWidgetItem *current);

private slots:
    void on_pushButton_input_clicked();

    void on_radioButton_message_toggled(bool checked);

    void on_radioButton_friends_toggled(bool checked);

    void on_radioButton_settings_toggled(bool checked);

    void on_pushButton_addFriend_clicked();

    void on_pushButton_friendRequest_clicked();

    void on_pushButton_addThisUser_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::MainWindow *ui;

    QMap<QListWidgetItem*, QTextDocument*> documents;
    QMap<QTextDocument*, int> documentToOID;

    void setRootFrameFormat(QTextDocument *doc);

    void insertLeftFrame(QTextDocument *doc, const QString &title, const QString &text);

    void insertRightFrame(QTextDocument *doc, const QString &title,const QString &text);
};

#endif // MAINWINDOW_H
