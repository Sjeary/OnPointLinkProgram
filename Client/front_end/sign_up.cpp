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

void Sign_up::signUpSuccess(QString ID)
{

}
void Sign_up::signUpFailed(QString log)
{

}


void Sign_up::on_pushButton_signUp_clicked()
{
    if(ui->lineEdit_nickname->text().isEmpty())
    {
        QMessageBox::warning(this, "can not sign up", "Please input nickname");
        return;
    }
    if(ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::warning(this, "can not sign up", "Please input password");
        return;
    }
    if(ui->lineEdit_password->text() != ui->lineEdit_confirmPassword->text())
    {
        QMessageBox::warning(this, "can not sign up", "The two passwords is different");
        return;
    }

    emit sendSignUp(ui->lineEdit_nickname->text(), ui->lineEdit_password->text());

    ui->lineEdit_nickname->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_confirmPassword->clear();
    this->close();
}

