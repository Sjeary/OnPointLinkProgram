#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QWidget>

namespace Ui {
class creategroup;
}

class creategroup : public QWidget
{
    Q_OBJECT

public:
    explicit creategroup(QWidget *parent = nullptr);
    ~creategroup();

signals:
    void sendCreateRequest(QStringList memberIDList);

private:
    Ui::creategroup *ui;
    QStringList memberIDList;

public slots:
    void addFriendItem(QString ID, QString nowStatus);
    void clearCreateGroupItem();


private slots:
    void on_pushButton_confirm_clicked();
};

#endif // CREATEGROUP_H
