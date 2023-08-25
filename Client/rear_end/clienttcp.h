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
    void getMessage(QByteArray content);

public slots:
    void tryConnect(QString IP, int port);
    void toSendMessage(QByteArray content);

private:
    QTcpSocket * m_tcp;


};

#endif // CLIENTTCP_H
