#ifndef NEWTEMPGROUP_H
#define NEWTEMPGROUP_H

#include <QWidget>

namespace Ui {
class NewTempGroup;
}

class NewTempGroup : public QWidget
{
    Q_OBJECT

public:
    explicit NewTempGroup(QWidget *parent = nullptr);
    ~NewTempGroup();

private slots:
    void on_pushButton_confirm_clicked();

signals:
    void giveNewGroupName(QString groupname);

private:
    Ui::NewTempGroup *ui;
};

#endif // NEWTEMPGROUP_H
