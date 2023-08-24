#include "core.h"
#include "front_end/login.h"
#include "front_end/sign_up.h"
#include "front_end/switchserverip.h"
#include "front_end/mainwindow.h"

Core::Core(QObject *parent)
    : QObject{parent}
{
    login = new Login();
    sign_up = new Sign_up();
    switchServerIP = new SwitchServerIP();
    mainwindow = new MainWindow();

    login->show();

    mainwindow->addMessageItem("me");

    connect(login, &Login::gotoSignUp, sign_up, &QWidget::show);
    connect(login, &Login::gotoSwitchServerIP, switchServerIP, &QWidget::show);

    connect(login, &Login::sendLogin, mainwindow, &QWidget::show);
    connect(login, &Login::sendLogin, login, &QWidget::close);

    connect(switchServerIP, &SwitchServerIP::sendNewIP, this, [this](QString newIP){
        this->serverIP = newIP;
    });
}

Core::~Core()
{
    login->deleteLater();
    sign_up->deleteLater();
    switchServerIP->deleteLater();
    mainwindow->deleteLater();
}
