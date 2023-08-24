#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void gotoSignUp();
    void gotoSwitchServerIP();
    void sendLogin(QString ID, QString password);

private slots:
    void on_pushButton_SignUp_clicked();

    void on_pushButton_switchServerIP_clicked();

    void on_pushButton_Login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
