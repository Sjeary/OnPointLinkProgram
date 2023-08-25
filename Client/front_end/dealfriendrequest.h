#ifndef DEALFRIENDREQUEST_H
#define DEALFRIENDREQUEST_H

#include <QWidget>

namespace Ui {
class DealFriendRequest;
}

class DealFriendRequest : public QWidget
{
    Q_OBJECT

public:
    explicit DealFriendRequest(QWidget *parent = nullptr);
    ~DealFriendRequest();

signals:
    void acceptRequest(QString ID);
    void rejectRequest(QString ID);

public slots:
    void addRequestItem(QString ID, QString nickname);

private:
    Ui::DealFriendRequest *ui;
};

#endif // DEALFRIENDREQUEST_H
