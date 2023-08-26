#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();

signals:
    void connected(QTcpSocket *);
    void received(QTcpSocket *);

public slots:
    void initServer();
    void send(QHostAddress ip, quint16 port, QByteArray &text);

private:
    QTcpServer * m_s;
    QList<QTcpSocket *> connections;
    QTime time;
};

#endif // TCPSERVER_H
