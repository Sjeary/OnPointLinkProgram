#include "mainmenu.h"
#include "ui_mainmenu.h"

#include <QIcon>
#include <QWidget>

void MainMenu::openSettingWindow() {
    settingWindow = new SettingWindow();
    settingWindow ->setWindowTitle("OnPointLink: 账号设置");
    settingWindow->exec();
}

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this -> setWindowTitle(QString("OnPointLink"));
    QMenuBar* toolBar = this -> menuBar();
    QIcon settingIcon = QIcon(":/MainMenu/settingIcon.png");
    QAction* settingAction = new QAction(settingIcon,tr(""),toolBar);
    toolBar -> addAction(settingAction);
    connect(settingAction,&QAction::triggered,this,&MainMenu::openSettingWindow);
}

MainMenu::~MainMenu()
{
    delete ui;
}

