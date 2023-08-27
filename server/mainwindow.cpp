/*
 * ============================
 * mainwindow.cpp
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 MainWindow 类的成员函数
 * ============================
 *
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
