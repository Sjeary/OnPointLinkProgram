/*
 * ============================
 * dealfriendrequest.cpp
 * 开发者：王钟骐
 * Update time: 2023-8-27
 *
 * 定义 DealFriendRequest 类成员函数
 * ============================
 *
*/

#include "dealfriendrequest.h"
#include "ui_dealfriendrequest.h"

#include <QMenu>
#include <QCursor>

DealFriendRequest::DealFriendRequest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DealFriendRequest)
{
    ui->setupUi(this);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    QMenu *menu = new QMenu(this);
    QAction *accept = new QAction(this), *reject = new QAction(this);
    accept->setText("accept");
    reject->setText("reject");
    menu->addAction(accept);
    menu->addAction(reject);

    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, [menu](){
        menu->exec(QCursor::pos());
    });
    connect(accept, &QAction::triggered, this, [this](){
        emit this->dealFriendRequest(ui->listWidget->currentItem()->toolTip(), true);
    });
    connect(reject, &QAction::triggered, this, [this](){
        emit this->dealFriendRequest(ui->listWidget->currentItem()->toolTip(), false);
    });
}

DealFriendRequest::~DealFriendRequest()
{
    delete ui;
}

void DealFriendRequest::addRequestItem(QString ID, QString message)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(ID + " message: " + message);
    item->setToolTip(ID);
    ui->listWidget->addItem(item);
}
