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
    void dealFriendRequest(QString ID, bool accept);

public slots:
    void addRequestItem(QString ID, QString message);

private:
    Ui::DealFriendRequest *ui;
};

#endif // DEALFRIENDREQUEST_H
