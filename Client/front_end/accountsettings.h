#ifndef ACCOUNTSETTINGS_H
#define ACCOUNTSETTINGS_H

#include <QWidget>
#include "ui_accountsettings.h"

namespace Ui{
    class AccountSettings;
}

class AccountSettings : public QWidget
{
    Q_OBJECT
public:
    explicit AccountSettings(QWidget *parent = nullptr);
    ~AccountSettings();

signals:

private:
    Ui::AccountSettings *ui;
};

#endif // ACCOUNTSETTINGS_H
