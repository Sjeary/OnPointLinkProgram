#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = nullptr);
    ~AddFriend();

signals:
    void sendSearchRequest(QString ID, QString nickname);

public slots:

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
