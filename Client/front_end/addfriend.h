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
    void getInfo(QString ID);

public slots:
    void getInfoFailed();

private slots:
    void on_pushButton_search_clicked();

private:
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
