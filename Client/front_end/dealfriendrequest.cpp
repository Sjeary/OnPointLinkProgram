#include "dealfriendrequest.h"
#include "ui_dealfriendrequest.h"

DealFriendRequest::DealFriendRequest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DealFriendRequest)
{
    ui->setupUi(this);
}

DealFriendRequest::~DealFriendRequest()
{
    delete ui;
}

void DealFriendRequest::addRequestItem(QString ID, QString nickname)
{
    ui->listWidget->addItem(nickname+" : "+ID);
}
