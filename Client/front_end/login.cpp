/*
 * ============================
 * login.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 Login 类成员函数
 * ============================
 *
*/

#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QCheckBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    received = false;
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
    if (!received)
        received = true;
    QMessageBox::information(this, "information", "Login success!");
    this->close();
}

void Login::loginFailed(QString log)
{
    QMessageBox::warning(this, "Login failed", log);
    if (!received)
        received = true;
    if (!ui->pushButton_Login->isEnabled()) {
        ui->pushButton_Login->setText("Login");
        ui->pushButton_Login->setEnabled(true);
    }
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
    received = false;
    bool remember_password = ui->checkBox_rememberPassword->isChecked();
    bool auto_login = ui->checkBox_autoLogin->isChecked();
    emit sendLogin(ui->comboBox->currentText(),
                   ui->lineEdit->text(),
                   remember_password,
                   auto_login);
    ui->pushButton_Login->setText("Login-ing");
    ui->pushButton_Login->setEnabled(false);

    // 登录超时计时模块
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Login::loginPassTime);
    qDebug() << "start login timing" << endl;
    timer->start(1000);
    qDebug() << "timing end" << endl;
}

void Login::loginPassTime()
{
    if (!this->received) {
        QMessageBox:: warning(this,"登录超时","登录超时，请重试");
        ui->pushButton_Login->setText("Login");
        ui->pushButton_Login->setEnabled(true);
    }
    if(timer->isActive()) {
        timer->stop();
    }
    return;
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
