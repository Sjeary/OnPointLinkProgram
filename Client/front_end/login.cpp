/*
 * ============================
 * login.cpp
 * 开发者：王钟骐、祝文轩
 * Update time: 2023-8-27
 *
 * 定义 Login 类成员函数
 * ============================
 *
*/

#include "login.h"
#include "ui_login.h"

#include <QMessageBox>

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

void Login::connectedToServer()
{
    ui->label_status->setText("server connected!");
}
void Login::cannotConnect()
{
    ui->label_status->setText("cannot connect, ");
}
void Login::loginSuccess()
{
    QMessageBox::information(this, "information", "Login success!");
    this->close();
}
void Login::loginFailed(QString log)
{
    QMessageBox::warning(this, "Login failed", log);
    ui->pushButton_Login->setText("Login");
    ui->pushButton_Login->setEnabled(true);
}

void Login::on_pushButton_SignUp_clicked()
{
    emit gotoSignUp();
}


void Login::on_pushButton_switchServerIP_clicked()
{
    emit gotoSwitchServerIP();
}


void Login::on_pushButton_Login_clicked()
{
    emit sendLogin(ui->comboBox->currentText(), ui->lineEdit->text(), ui->checkBox_rememberPassword, ui->checkBox_autoLogin);
    ui->pushButton_Login->setText("Login-ing");
    ui->pushButton_Login->setEnabled(false);
}


void Login::on_pushButton_connect_clicked()
{
    emit reconnectToServer();
}

void Login::writeSavedAccountInfo(const QString& savedOID,const QString &savedPassword) {
    /*
     * writeSavedAccountInfo
     * updated by 祝文轩
     * 作用：写入上次登录的用户的OID、Password（需要上次登录的用户勾选记住密码
    */
    ui->comboBox->setEditText(savedOID);
    ui->lineEdit->setText(savedPassword);
}

void Login::turnToWaiting(){
    ui->pushButton_Login->setText("Login-ing");
}
