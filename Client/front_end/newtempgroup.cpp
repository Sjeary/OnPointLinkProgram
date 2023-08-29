#include "newtempgroup.h"
#include "ui_newtempgroup.h"

newtempgroup::newtempgroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newtempgroup)
{
    ui->setupUi(this);
}

newtempgroup::~newtempgroup()
{
    delete ui;
}

void newtempgroup::on_pushButton_confirm_clicked()
{
    QString groupname = ui->textEdit_newgroup->toPlainText();
    emit giveNewGroupName(groupname);
    this->close();
}
