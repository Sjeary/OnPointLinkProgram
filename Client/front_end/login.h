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
    void reconnectToServer();
    void sendLogin(QString ID, QString password, bool rememberPassword, bool autoLogin);

public slots:
    void connectedToServer();
    void cannotConnect();
    void loginSuccess();
    void loginFailed(QString log = "");
    void writeSavedAccountInfo(const QString &savedOID, const QString &savedPassword);

private slots:
    void on_pushButton_SignUp_clicked();

    void on_pushButton_switchServerIP_clicked();

    void on_pushButton_Login_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
