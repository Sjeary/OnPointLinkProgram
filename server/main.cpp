#include "mainwindow.h"

#include <QApplication>
#include <tcpserver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TcpServer s;
    w.show();
    return a.exec();
}
