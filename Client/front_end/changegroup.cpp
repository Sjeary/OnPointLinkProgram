#include "changegroup.h"
#include "ui_changegroup.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QFile>

changegroup::changegroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changegroup)
{
    ui->setupUi(this);
    ui->tableWidget_changegroup->setColumnCount(2);
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item0->setText("分组");
    item1->setText("选择");
    ui->tableWidget_changegroup->setHorizontalHeaderItem(0, item0);
    ui->tableWidget_changegroup->setHorizontalHeaderItem(1, item1);
    ui->tableWidget_changegroup->insertRow(0);
    ui->tableWidget_changegroup->insertRow(1);
    QTableWidgetItem* group1 = new QTableWidgetItem;
    group1->setText("我的好友");
    QTableWidgetItem* status = new QTableWidgetItem;
    status->setText("no");
    ui->tableWidget_changegroup->setItem(0, 0, group1);
    ui->tableWidget_changegroup->setItem(0, 1, status);
    QTableWidgetItem* group2 = new QTableWidgetItem;
    group2->setText("黑名单");
    QTableWidgetItem* status1 = new QTableWidgetItem;
    status1->setText("no");
    ui->tableWidget_changegroup->setItem(1, 0, group2);
    ui->tableWidget_changegroup->setItem(1, 1, status1);


    connect(ui->tableWidget_changegroup, &QTableWidget::cellClicked, this, [this]()
    {
        QTableWidgetItem *item = ui->tableWidget_changegroup->currentItem();
        int nowRow = item->row();
        int nowColumn = item->column();
        qDebug() << nowColumn;
        if (nowColumn > 0)
        {
            if (item->text() == "yes") {
                item->setText("no");
                QTableWidgetItem *itemname = ui->tableWidget_changegroup->item(nowRow, nowColumn-1);
                QString groupName = itemname->text();
                groupList.removeAll(groupName);
            }
            else if(item->text() == "no")
            {
                item->setText("yes");
                QTableWidgetItem *itemname = ui->tableWidget_changegroup->item(nowRow, nowColumn-1);
                QString groupName = itemname->text();
                groupList.append(groupName);
            }
        }
        else
        {
            qDebug() <<"please click right one";
        }

    });
}

changegroup::~changegroup()
{
    delete ui;
}

void changegroup::addGroupItem(QString groupname, QString nowStatus)
{
    // Check if the groupname already exists in the table
    for (int row = 0; row < ui->tableWidget_changegroup->rowCount(); ++row) {
        QTableWidgetItem* existingGroupItem = ui->tableWidget_changegroup->item(row, 0);
        if (existingGroupItem && existingGroupItem->text() == groupname) {
            // If the groupname already exists, return without adding a new row
            return;
        }
    }

    // If the groupname doesn't exist, add a new row
    int curRow = ui->tableWidget_changegroup->rowCount();
    ui->tableWidget_changegroup->insertRow(curRow);

    QTableWidgetItem* group1 = new QTableWidgetItem;
    group1->setText(groupname);
    QTableWidgetItem* status = new QTableWidgetItem;
    status->setText("no");

    ui->tableWidget_changegroup->setItem(curRow, 0, group1);
    ui->tableWidget_changegroup->setItem(curRow, 1, status);
}

void changegroup::on_pushButton_confirm_clicked()
{

    if(groupList.size() == 1)
    {
        emit sendChangeGroup(changeID, groupList.at(0));
    }
    else
    {
        QMessageBox::warning(this, "change failed", "you can only choose one group");
    }
    this->close();
}

void changegroup::clearChangeGroupItem()
{
    for (int i = 0; i < ui->tableWidget_changegroup->rowCount(); i++) {
        QTableWidgetItem* item1 = ui->tableWidget_changegroup->item(i, 0);
        if(item1->text() == "我的好友"||item1->text() == "黑名单")
        {
            continue;
        }
        else
        {
            ui->tableWidget_changegroup->removeRow(i);
            i--;
        }
    }
}

void changegroup::receiveID(QString ID)
{
    changeID = ID;
}

void changegroup::on_pushButton_new_clicked()
{
    emit gotoNewGroup();
}

void changegroup::newGroupName(QString groupname)
{
    int curRow = ui->tableWidget_changegroup->rowCount();
    ui->tableWidget_changegroup->insertRow(curRow);

    QTableWidgetItem* group1 = new QTableWidgetItem;
    group1->setText(groupname);
    QTableWidgetItem* status = new QTableWidgetItem;
    status->setText("no");

    ui->tableWidget_changegroup->setItem(curRow, 0, group1);
    ui->tableWidget_changegroup->setItem(curRow, 1, status);
}
