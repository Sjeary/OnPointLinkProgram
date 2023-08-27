/*
 * ============================
 * mainwindow.h
 * 开发者：希望之花团队
 * Update time: 2023-8-27
 *
 * 定义 MainWindow 类
 * 在namespace Ui 当中声明 MainWindow 类
 * ============================
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
