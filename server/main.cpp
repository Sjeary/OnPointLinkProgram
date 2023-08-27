/*
 * ============================
 * main.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 服务端主程序
 * ============================
 *
*/

#include "mainwindow.h"
#include "tcpserver.h"
#include "servercore.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TcpServer s;
    servercore sc(&s);
    w.show();
    return a.exec();
}
