#include "creategroup.h"
#include "ui_creategroup.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QFile>

creategroup::creategroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creategroup)
{
    ui->setupUi(this);
    ui->createGroupList->setColumnCount(2);
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item0->setText("OID");
    item1->setText("选择");
    ui->createGroupList->setHorizontalHeaderItem(0, item0);
    ui->createGroupList->setHorizontalHeaderItem(1, item1);

    connect(ui->createGroupList, &QTableWidget::cellClicked, this, [this]()
    {
        QTableWidgetItem *item = ui->createGroupList->currentItem();
        int nowRow = item->row();
        int nowColumn = item->column();
        qDebug() << nowColumn;
        if (nowColumn > 0)
        {
            if (item->text() == "yes") {
                item->setText("no");
                QTableWidgetItem *itemID = ui->createGroupList->item(nowRow, nowColumn-1);
                QString ID = itemID->text();
                memberIDList.removeAll(ID);
            }
            else if(item->text() == "no")
            {
                item->setText("yes");
                QTableWidgetItem *itemID = ui->createGroupList->item(nowRow, nowColumn-1);
                QString ID = itemID->text();
                memberIDList.append(ID);
            }
        }
        else
        {
            qDebug() <<"please click right one";
        }

    });
}

creategroup::~creategroup()
{
    delete ui;
}

void creategroup::addFriendItem(QString ID, QString nowStatus)
{
    int curRow = ui->createGroupList->rowCount();
    ui->createGroupList->insertRow(curRow);

    QTableWidgetItem* ID1 = new QTableWidgetItem;
    ID1->setText(ID);
    QTableWidgetItem* status = new QTableWidgetItem;
    status->setText("no");

    ui->createGroupList->setItem(curRow, 0, ID1);
    ui->createGroupList->setItem(curRow, 1, status);
}

void creategroup::on_pushButton_confirm_clicked()
{
    if(memberIDList.size() > 1)
    {
        emit sendCreateRequest(memberIDList);
    }
    else
    {
        QMessageBox::warning(this, "create failed", "A group should have there member at least.");
    }
}

void creategroup::clearCreateGroupItem()
{
    ui->createGroupList->clear();
    ui->createGroupList->setRowCount(0);
}
