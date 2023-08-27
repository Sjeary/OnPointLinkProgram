/*
 * ============================
 * switchserverip.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 SwitchServerIP 类成员函数
 * ============================
 *
*/

#include "switchserverip.h"
#include "ui_switchserverip.h"

SwitchServerIP::SwitchServerIP(QWidget *parent, QString oldIP) :
    QWidget(parent),
    ui(new Ui::SwitchServerIP)
{
    ui->setupUi(this);
    ui->lineEdit->setText(oldIP);
}

SwitchServerIP::~SwitchServerIP()
{
    delete ui;
}

void SwitchServerIP::on_pushButton_clicked()
{
    emit sendNewIP(ui->lineEdit->text());
    this->close();
}

