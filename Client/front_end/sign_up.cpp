#include "sign_up.h"
#include "ui_sign_up.h"

sign_up::sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign_up)
{
    ui->setupUi(this);
}

sign_up::~sign_up()
{
    delete ui;
}
