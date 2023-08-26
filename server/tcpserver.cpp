#include "tcpserver.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    initServer();
}

TcpServer::~TcpServer()
{
    delete m_s;
}

void TcpServer::initServer()
{
    m_s = new QTcpServer;
    unsigned short port = 6666;
    m_s->listen(QHostAddress::Any, port);
    connect(m_s, &QTcpServer::newConnection, [&]() {
        while (m_s->hasPendingConnections()) {
            QTcpSocket *clientSocket = m_s->nextPendingConnection();
            emit connected(clientSocket);
            connections.append(clientSocket);

            qDebug() << "New client connected.";

            connect(clientSocket, &QTcpSocket::readyRead, [=]() {
                emit received(clientSocket);
                QByteArray data = clientSocket->readAll();
                qDebug() << "Received data from client:" << data;

//                QHostAddress targetIP = clientSocket->peerAddress();
//                quint16 targetPort = clientSocket->peerPort();
//                send(targetIP, targetPort, data);

//这里还不知道数据结构是什么，获取ip和port的代码确定以后再写
                // Assuming data contains the target client's IP and port
//                QString targetIP = QString(data);
//                quint16 targetPort = 12346; // Port of the target client

//                send(targetIP, targetPort, data);
            });

            connect(clientSocket, &QTcpSocket::disconnected, [=]() {
                qDebug() << "Client disconnected.";
                emit disconnected(clientSocket);
                connections.removeOne(clientSocket);
                clientSocket->deleteLater();
            });
        }
    });
}

void TcpServer::send(QHostAddress ip, quint16 port, QByteArray &text)
{
    foreach (QTcpSocket *targetSocket, connections) {
        if (targetSocket->peerAddress() == ip &&
            targetSocket->peerPort() == port) {
            targetSocket->write(text);
            targetSocket->flush();
            qDebug() << "Data forwarded to target client.";
            break;
        }
    }
}

void TcpServer::sendJsonObject(QHostAddress ip, quint16 port, const QJsonObject &obj) { // 新函数，updated by zwx
    QJsonDocument docu(obj);
    QByteArray array = docu.toJson();
    //这里少一个传回到客户端json文件的函数，但是我不知道接口怎么写
    send(ip, port, array);
}
