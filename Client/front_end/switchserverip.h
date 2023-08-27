/*
 * ============================
 * switchserverip.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 SwitchServerIP 类
 * 声明 SwitchServerIP 类的成员函数
 * ============================
 *
*/

#ifndef SWITCHSERVERIP_H
#define SWITCHSERVERIP_H

#include <QWidget>

namespace Ui {
    class SwitchServerIP;
}

class SwitchServerIP : public QWidget
/*
 * SwitchServerIP
 * 自定义服务器IP的窗口
*/
{
    Q_OBJECT

public:
    explicit SwitchServerIP(QWidget *parent = nullptr, QString oldIP = "");
    ~SwitchServerIP();

signals:
    void sendNewIP(QString IP);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SwitchServerIP *ui;
};

#endif // SWITCHSERVERIP_H
