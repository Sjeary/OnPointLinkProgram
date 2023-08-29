#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->port_2->setText("8899");
    //创建一个监听器服务对象
    //Tcpserver
    m_s=new QTcpServer(this);
    m_tcp = new QTcpSocket;
    //启动监听   通过点击监听按钮实现，并且在按钮转到的槽函数实现监听
    //上述完成监听，就等待用户/客户端的链接
    connect(m_s,&QTcpServer::newConnection,this,[=](){
        //状态栏变色
        m_status->setPixmap(QPixmap(":/a/tmp/connect.png").scaled(20,20));
        //程序到此步骤证明有用户链接，启用socket通信传输并解析数据
        //实例此次通信对象  nextPendingConnection得到一个可供通信的套接字对象
        m_tcp=m_s->nextPendingConnection();
        QString client_ip = m_tcp->peerAddress().toString().split("::ffff:")[1];
        quint16 client_port = m_tcp->peerPort();

        ui->record->append(tr("%1:%2 connected!\n").arg(client_ip).arg(client_port));
        //进行对象处理，检测传输的数据,利用connect对tcp套接字操作
        connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
                QByteArray array = m_tcp->readAll();
                ui->record->append("客户端说："+array);
        });

        //客户端断开操作
        connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
            QString client_ip = m_tcp->peerAddress().toString().split("::ffff:")[1];
            quint16 client_port = m_tcp->peerPort();

            ui->record->append(tr("%1:%2 Disconnected!\n").arg(client_ip).arg(client_port));
            m_tcp->disconnectFromHost();
            if(m_tcp->state() == QAbstractSocket::UnconnectedState
                    || m_tcp->waitForDisconnected(1000))
                qDebug("Disconnected!\n");
            else
                qDebug("Disconnect fail!\n");
            m_status->setPixmap(QPixmap(":/a/tmp/disconnect.png").scaled(20,20));
        });
    });
    //增加一点动画效果   状态栏的颜色变化
   m_status =new QLabel;
   //状态栏的图片添加
   //m_status->setPixmap(QPixmap(":/a/tmp/connect.png").scaled(20,20));
   ui->statusbar->addWidget(new QLabel("链接状态："));
   ui->statusbar->addWidget(m_status);
   //装到菜单状态栏


}

MainWindow::~MainWindow()
{
    delete ui;
}

//点击监听服务，自然而然去启动监听服务
void MainWindow::on_setlisten_clicked()
{  setWindowTitle("服务器");
    //得到窗口 lineedit窗口的端口号
    unsigned  short  port=ui->port_2->text().toShort();
    //进行监听   ip   端口
    m_s->listen(QHostAddress::Any,port);
    ui->setlisten->setDisabled(true);
}

void MainWindow::on_send_clicked()
{
    //把发出信息框的数据拿到，通过socket套接字发送出去
    QString string=ui->sendmsg->toPlainText();
    m_tcp->write(string.toUtf8());
    ui->record->append("服务端说："+string);
    ui->sendmsg->clear();
}
