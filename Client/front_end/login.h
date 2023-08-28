/*
 * ============================
 * login.h
 * 开发者：王钟骐、祝文轩
 * Update time: 2023-8-27
 *
 * 定义 Login 类
 * 声明 Login 类的成员函数
 * ============================
 *
*/

#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class login;
}

class Login : public QWidget
/*
 * Login
 * 用户登录窗口
*/
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
    //尝试连接到服务器
    void connectedToServer();
    //无法链接
    void cannotConnect();
    //成功登录
    void loginSuccess();
    //登录失败
    void loginFailed(QString log = "");

    /*一些供外部程序修改ui的接口*/
    void writeSavedAccountInfo(const QString &savedOID, const QString &savedPassword);
    void turnToWaiting();

private slots:
    void on_pushButton_SignUp_clicked();

    void on_pushButton_switchServerIP_clicked();

    void on_pushButton_Login_clicked();

    void on_pushButton_connect_clicked();

    void loginPassTime(); //  超时函数

private:
    Ui::login *ui;
    bool received; // 在验证是否登录超时时有用
    QTimer* timer; // 超时计时器
};

#endif // LOGIN_H
