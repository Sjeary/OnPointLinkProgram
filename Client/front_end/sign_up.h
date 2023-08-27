/*
 * ============================
 * sign_up.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 Sign_up 类
 * 声明 Sign_up 类的成员函数
 * ============================
 *
*/

#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>

namespace Ui {
    class sign_up;
}

class Sign_up : public QWidget
/*
 * Sign_up
 * 用户注册主窗口
*/
{
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

signals:
    void sendSignUp(QString nickname, QString password);

public slots:
    void signUpSuccess(QString ID);
    void signUpFailed(QString log);

private slots:
    void on_pushButton_signUp_clicked();

private:
    Ui::sign_up *ui;
};

#endif // SIGN_UP_H
