#include "newtempgroup.h"
#include "ui_newtempgroup.h"

NewTempGroup::NewTempGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewTempGroup)
{
    ui->setupUi(this);
}

NewTempGroup::~NewTempGroup()
{
    delete ui;
}

void NewTempGroup::on_pushButton_confirm_clicked()
{
    QString groupname = ui->textEdit_newgroup->toPlainText();
    emit giveNewGroupName(groupname);
    this->close();
}
