#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QLabel>
#include <QHostAddress>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle(QString("客户端"));
    ui->setupUi(this);
    ui->port_2->setText("8899");
    ui->ip->setText("127.0.0.1");
    //刚开始 客户端的 [断开服务] 按钮不可用
    ui->disconnect->setDisabled(true);
    //创建一个监听器服务对象
    //Tcpserver
    m_tcp=new QTcpSocket(this);

    //客户端 被动的接收服务器信号
    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray array=m_tcp->readAll();
        ui->record->append("服务端说："+array);
    });
    //客户端   断开
    connect(m_tcp,&QTcpSocket::disconnected,this,[=](){
        m_status->setPixmap(QPixmap(":/a/tmp/disconnect.png").scaled(20,20));
        ui->record->append("断开链接服务器");
        ui->connect->setDisabled(false);
        ui->disconnect->setDisabled(true);
    });
    //操作状态栏图标
    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        m_status->setPixmap(QPixmap(":/a/tmp/connect.png").scaled(20,20));
        ui->record->append("已经链接成功服务器");

        //操作按钮互斥，链接成功了，自然链接按钮不能用只有断开按钮可以用
        ui->connect->setDisabled(true);
        ui->disconnect->setDisabled(false);
    });
    //增加一点动画效果   状态栏的颜色变化
   m_status =new QLabel;
   //状态栏的图片添加
   ui->statusbar->addWidget(new QLabel("链接状态："));
   ui->statusbar->addWidget(m_status);
   //装到菜单状态栏


}

MainWindow::~MainWindow()
{
    delete ui;
}

//点击监听服务，自然而然去启动监听服务


void MainWindow::on_send_clicked()
{
    //把发出信息框的数据拿到，通过socket套接字发送出去
    QString string=ui->sendmsg->toPlainText();
    m_tcp->write(string.toUtf8());
    ui->record->append("客户端说："+string);
    ui->sendmsg->clear();
}

void MainWindow::on_connect_clicked()
{
    //获取 IP 端口   才能链接
   QString  ip=ui->ip->text();
   unsigned  short port=ui->port_2->text().toUShort();
   qDebug("click_on_connect state = %d\n",m_tcp->state());
   m_tcp->connectToHost(QHostAddress(ip),port);
   if(m_tcp->waitForConnected(1000)) {
        qDebug("connected !\n");
        ui->record->clear();
   }
   else
       qDebug("connect out time limit !\n");

}

void MainWindow::on_disconnect_clicked()
{
    qDebug("loc1 state = %d\n",m_tcp->state());
    m_tcp->disconnectFromHost();
    qDebug("loc2 state = %d\n",m_tcp->state());
    if(m_tcp->state() == QAbstractSocket::UnconnectedState
            || m_tcp->waitForDisconnected(1000))
        qDebug("Disconnected!\n");
    else
        qDebug("Disconnect fail!\n");
    m_tcp->close();
    ui->connect->setDisabled(false);
    ui->disconnect->setDisabled(false);
}
