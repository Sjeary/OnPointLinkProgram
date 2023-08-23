#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_SignUp_clicked()
{
    emit gotoSignUp();
}


void Login::on_pushButton_switchServerIP_clicked()
{
    emit gotoSwitchServerIP();
}

