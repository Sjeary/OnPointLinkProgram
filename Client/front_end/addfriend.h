/*
 * ============================
 * addfriend.h
 * 开发者：王钟骐
 * Update time: 2023-8-27
 *
 * 定义 AddFriend 类
 * 声明 AddFriend 类的成员函数
 * ============================
 *
*/

#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

namespace Ui {
    class AddFriend;
}

class AddFriend : public QWidget
/*
 * AddFriend
 * 添加好友的GUI窗口
*/
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();

signals:
    //发送获得用户信息请求
    void getInfo(QString ID);

public slots:
    void getInfoFailed();

private slots:
    void on_pushButton_search_clicked();

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
