#include "addfriend.h"
#include "ui_addfriend.h"

#include <QMessageBox>

AddFriend::AddFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_pushButton_search_clicked()
{
    emit getInfo(ui->lineEdit_input->text());
}

void AddFriend::getInfoFailed()
{
    QMessageBox::warning(this, "get user info failed", "No such user OID");
}
