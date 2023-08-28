#include "accountsettings.h"

AccountSettings::AccountSettings(QWidget *parent) :
    QWidget(parent),ui(new Ui::AccountSettings)
{
    ui->setupUi(this);
}

AccountSettings::~AccountSettings()
{
    delete ui;
}
