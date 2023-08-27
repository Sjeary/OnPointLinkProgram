/*
 * ============================
 * main.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 客户端主程序
 * ============================
 *
*/

#include "core.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Core core;

    return a.exec();
}
