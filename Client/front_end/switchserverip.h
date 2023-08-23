#ifndef SWITCHSERVERIP_H
#define SWITCHSERVERIP_H

#include <QWidget>

namespace Ui {
class SwitchServerIP;
}

class SwitchServerIP : public QWidget
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
