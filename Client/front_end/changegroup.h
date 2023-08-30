#ifndef CHANGEGROUP_H
#define CHANGEGROUP_H

#include <QWidget>

namespace Ui {
class ChangeGroup;
}

class ChangeGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeGroup(QWidget *parent = nullptr);
    ~ChangeGroup();

private:
    Ui::ChangeGroup *ui;
    QStringList groupList;
    QString changeID;

signals:
    void sendChangeGroup(QString ID, QString groupList);
    void gotoNewGroup();

public slots:
    void addGroupItem(QString ID, QString nowStatus);
    void clearChangeGroupItem();
    void receiveID(QString ID);
    void newGroupName(QString groupname);

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_new_clicked();
};

#endif // CHANGEGROUP_H
