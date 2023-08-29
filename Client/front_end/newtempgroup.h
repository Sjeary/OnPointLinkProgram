#ifndef NEWTEMPGROUP_H
#define NEWTEMPGROUP_H

#include <QWidget>

namespace Ui {
class newtempgroup;
}

class newtempgroup : public QWidget
{
    Q_OBJECT

public:
    explicit newtempgroup(QWidget *parent = nullptr);
    ~newtempgroup();

private slots:
    void on_pushButton_confirm_clicked();

signals:
    void giveNewGroupName(QString groupname);

private:
    Ui::newtempgroup *ui;
};

#endif // NEWTEMPGROUP_H
