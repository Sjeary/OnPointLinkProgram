#ifndef CORE_H
#define CORE_H

#include <QObject>

class Login;
class Sign_up;
class SwitchServerIP;
class MainWindow;

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

protected:

private:
    Login *login;
    Sign_up *sign_up;
    SwitchServerIP *switchServerIP;
    MainWindow *mainwindow;
    QString serverIP;

signals:

};

#endif // CORE_H
