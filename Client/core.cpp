#include "core.h"
#include "front_end/login.h"
#include "front_end/sign_up.h"
#include "front_end/switchserverip.h"

Core::Core(QObject *parent)
    : QObject{parent}
{
    login = new Login();
    sign_up = new Sign_up();
    switchServerIP = new SwitchServerIP();

    login->show();


    connect(login, &Login::gotoSignUp, sign_up, &QWidget::show);
    connect(login, &Login::gotoSwitchServerIP, switchServerIP, &QWidget::show);

    connect(switchServerIP, &SwitchServerIP::sendNewIP, this, [this](QString newIP){
        this->serverIP = newIP;
    });
}

Core::~Core()
{
    login->deleteLater();
    sign_up->deleteLater();
    switchServerIP->deleteLater();
}
