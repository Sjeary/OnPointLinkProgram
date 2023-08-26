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
    void disconnected(QTcpSocket *);

public slots:
    void initServer();
    void send(QHostAddress ip, quint16 port, QByteArray &text);
    void sendJsonObject(QHostAddress ip, quint16 port, const QJsonObject &obj); // 新函数,updated by zwx.


private:
    QTcpServer * m_s;
    QList<QTcpSocket *> connections;
    QTime time;
};

#endif // TCPSERVER_H
