/*
 * ============================
 * clienttcp.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 ClientTcp 类
 * 声明 ClientTcp 类的成员函数
 * ============================
 *
*/

#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>

class QTcpSocket;

class ClientTcp : public QObject
{
    Q_OBJECT
public:
    explicit ClientTcp(QObject *parent = nullptr);

signals:
    void getConnect();
    void connectFailed();
    void sendMessageFailed();
    void getMessage(QByteArray content);

public slots:
    void tryConnect(QString IP, int port);
    void toSendMessage(QByteArray content);

private:
    QTcpSocket * m_tcp;


};

#endif // CLIENTTCP_H
