#include "clienttcp.h"

#include <QTcpSocket>

ClientTcp::ClientTcp(QObject *parent)
    : QObject{parent}
{
    m_tcp = new QTcpSocket(this);
    connect(m_tcp, &QTcpSocket::readyRead, [this](){
        emit this->getMessage(m_tcp->readAll());
    });
}


void ClientTcp::tryConnect(QString IP, int port)
{
    qDebug("click_on_connect state = %d\n",m_tcp->state());
    m_tcp->connectToHost(QHostAddress(IP), port);
    if(m_tcp->waitForConnected(1000)) {
        qDebug("connected !\n");
        emit getConnect();
    }
    else
        emit connectFailed();
}

void ClientTcp::toSendMessage(QByteArray content)
{
    m_tcp->write(content);
    qDebug()<<content;
}
