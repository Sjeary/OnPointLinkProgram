#include "clienttcp.h"

#include <QTcpSocket>

ClientTcp::ClientTcp(QObject *parent)
    : QObject{parent}
{
    m_tcp = new QTcpSocket(this);
    connect(m_tcp, &QTcpSocket::readyRead, this, [this](){
        QByteArray content = m_tcp->readAll();
        emit this->getMessage(content);
        qDebug()<<"receive: "<<content;
    });
}


void ClientTcp::tryConnect(QString IP, int port)
{
    qDebug("click_on_connect state = %d\n",m_tcp->state());
    m_tcp->connectToHost(QHostAddress(IP), port);
    if(m_tcp->waitForConnected(1000)) {
        qDebug()<<"connected!";
        emit getConnect();
    }
    else
    {
        qDebug()<<"cannot connect!";
        emit connectFailed();
    }
}

void ClientTcp::toSendMessage(QByteArray content)
{
    m_tcp->write(content);
    qDebug()<<"send: "<<content;
}
