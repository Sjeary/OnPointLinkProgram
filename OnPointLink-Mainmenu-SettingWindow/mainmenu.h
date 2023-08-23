#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "settingwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void openSettingWindow();

private:
    Ui::MainMenu *ui;
    SettingWindow* settingWindow;
};
#endif // MAINMENU_H
