/*
 * ============================
 * addfriend.cpp
 * 开发者：王钟骐
 * Update time: 2023-8-27
 *
 * 定义 AddFriend 类成员函数
 * ============================
 *
*/

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
