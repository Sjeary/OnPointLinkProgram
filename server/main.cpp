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
