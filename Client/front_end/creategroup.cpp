#include "creategroup.h"
#include "ui_creategroup.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
        if (item) {
            QString ID = item->text();
            memberIDList.append(ID);
        }
    });
}

creategroup::~creategroup()
{
    delete ui;
}

void creategroup::addFriendItem(QString ID, QString name)
{
    int curRow = ui->createGroupList->rowCount();
    ui->createGroupList->insertRow(curRow);

    QTableWidgetItem* ID1 = new QTableWidgetItem;
    ID1->setText(ID);

    ui->createGroupList->setItem(curRow, 0, ID1);
}

void creategroup::on_pushButton_confirm_clicked()
{
    emit sendCreateRequest(memberIDList);
    memberIDList.clear();
}
