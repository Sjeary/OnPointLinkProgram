#include "sign_up.h"
#include "ui_sign_up.h"

#include <QMessageBox>

Sign_up::Sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::on_pushButton_signUp_clicked()
{
    if(ui->lineEdit_password->text() != ui->lineEdit_confirmPassword->text())
    {
        QMessageBox::warning(this, "can not sign up", "The two passwords is different");
        return;
    }

    emit sendSignUP(ui->lineEdit_nickname->text(), ui->lineEdit_password->text());

    ui->lineEdit_nickname->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_confirmPassword->clear();
    this->close();
}

