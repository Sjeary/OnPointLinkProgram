#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include "ui_settingwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui{class SettingWindow;}
QT_END_NAMESPACE

class SettingWindow : public QDialog
{
    Q_OBJECT
public:
    explicit SettingWindow(QWidget *parent = nullptr);

signals:

private:
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
