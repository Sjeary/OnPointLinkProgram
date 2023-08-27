/*
 * ============================
 * dealfriendrequest.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 DealFriendRequest 类
 * 声明 DealFriendRequest 类的成员函数
 * ============================
 *
*/

#ifndef DEALFRIENDREQUEST_H
#define DEALFRIENDREQUEST_H

#include <QWidget>

namespace Ui {
    class DealFriendRequest;
}

class DealFriendRequest : public QWidget
/*
 * DealFriendRequest
 * 好友申请处理窗口
*/
{
    Q_OBJECT

public:
    explicit DealFriendRequest(QWidget *parent = nullptr);
    ~DealFriendRequest();

signals:
    void dealFriendRequest(QString ID, bool accept);

public slots:
    void addRequestItem(QString ID, QString message);

private:
    Ui::DealFriendRequest *ui;
};

#endif // DEALFRIENDREQUEST_H
