/*
 * ============================
 * mainwindow.cpp
 * 开发者：王钟骐、祝文轩、王启贤
 * Update time: 2023-8-27
 *
 * 定义 MainWindow 类成员函数
 * ============================
 *
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextFrame>
#include <QTextDocument>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    acSetting = nullptr;
    connect(ui->listWidget_message, &QListWidget::currentItemChanged, this, &MainWindow::changeMessageItem);

    ui->radioButton_message->setChecked(true);

    connect(ui->treeWidget_friend, &QTreeWidget::itemClicked, this, &MainWindow::treeItemClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getMessage(QString ID, QString name, QString content, bool isReceive)
{
    foreach (QTextDocument * const var, documentToOID.keys()) {
        if (documentToOID.value(var) == ID.toInt())
        {
            if(isReceive)
            {
                insertLeftFrame(var, name, content);
            }
            else
            {
                insertRightFrame(var, name, content);
            }
        }
    }
}

void MainWindow::getUserInfo(QString ID, QString name, QString ins, QString email, QString birth)
{
    ui->label_userInfo_OID->setText(ID);
    qDebug()<<ID;
    ui->textEdit_userInfo->clear();
    ui->textEdit_userInfo->insertPlainText("name:"+name+"\ninstruction:"+ins+"\nemail:"+email+"\nbirth"+birth);
}

void MainWindow::getFriendRequest()
{
    QMessageBox::information(this, "friend request", "you have received a friend request");
}

void MainWindow::addMessageItem(QString ID, QString name)
{
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setData(0,name + "\nID: "+ ID);
    newItem->setData(3,ID);
    ui->listWidget_message->addItem(newItem);
    QTextDocument *newDocument = new QTextDocument(this);
    documents.insert(newItem, newDocument);
    documentToOID.insert(newDocument, ID.toInt());
    setRootFrameFormat(newDocument);
}

void MainWindow::addFriendItem(QString ID, QString name, QString groupname)
{
    QListWidgetItem *newItem = new QListWidgetItem();
    newItem->setData(0,name + "\nID: " + ID);
    newItem->setData(3,ID);
    ui->listWidget_friend->addItem(newItem);
    //
    //if(groupname == "我的好友"){}
    int flag = 0;
    for (int i = 0; i < ui->treeWidget_friend->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *group = ui->treeWidget_friend->topLevelItem(i);
        if(group->text(0) == groupname)
        {
            QTreeWidgetItem *friend1 = new QTreeWidgetItem(group);
            friend1->setText(0, ID);
            flag = 1;
        }
    }
    if(flag == 0)
    {
        QTreeWidgetItem *group = new QTreeWidgetItem(ui->treeWidget_friend);
        group->setText(0, groupname);
        QTreeWidgetItem *friend1 = new QTreeWidgetItem(group);
        friend1->setText(0, ID);
    }
}

void MainWindow::clearMessageItem()
{
    ui->listWidget_message->clear();
}
void MainWindow::clearFriendItem()
{
    ui->listWidget_friend->clear();
    ui->treeWidget_friend->clear();
}

void MainWindow::on_pushButton_input_clicked()
{
    QString text = ui->plainTextEdit_input->toPlainText();
    ui->plainTextEdit_input->clear();

    insertRightFrame(ui->textEdit_show->document(),"me", text);

    emit sendMessage(QString::number(documentToOID[ui->textEdit_show->document()]), text);
}

void MainWindow::changeMessageItem(QListWidgetItem *current)
{
    QTextDocument *currentDocument = documents.value(current, nullptr);
    if (currentDocument == nullptr)
        return;
    ui->textEdit_show->setDocument(currentDocument);
}

void MainWindow::on_pushButton_addFriend_clicked()
{
    emit gotoAddFriend();
}

void MainWindow::on_pushButton_friendRequest_clicked()
{
    emit gotoDealFriendRequest();
}

void MainWindow::on_pushButton_addThisUser_clicked()
{
    emit sendAddFriendRequest(ui->label_userInfo_OID->text());
}

void MainWindow::on_radioButton_message_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_middle->setCurrentIndex(0);
        ui->stackedWidget_main->setCurrentIndex(0);
    }
}


void MainWindow::on_radioButton_friends_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_middle->setCurrentIndex(1);
        ui->stackedWidget_main->setCurrentIndex(1);
    }
}

void MainWindow::on_radioButton_settings_toggled(bool checked)
{
    if(checked)
    {
        ui->stackedWidget_middle->setCurrentIndex(2);
        ui->stackedWidget_main->setCurrentIndex(2);
        ui->stackedWidget_main->close();
        ui->stackedWidget_middle->close();
        if (acSetting == nullptr) {
            acSetting = new AccountSettings(this);
        }
        acSetting->show();
    }
    else
    {
        ui->stackedWidget_main->show();
        ui->stackedWidget_middle->show();
        acSetting->close();
    }
}

void MainWindow::setRootFrameFormat(QTextDocument *doc)
{
    QTextFrame *root_frame = doc->rootFrame();

    QTextFrameFormat root_frame_format = root_frame->frameFormat();//创建框架格式
    root_frame_format.setBorder(0);//设置边界宽度
    root_frame_format.setBackground(QColor("aliceblue"));//设置边界宽度
    root_frame->setFrameFormat(root_frame_format); //给框架使用格式
}

void MainWindow::insertLeftFrame(QTextDocument *doc, const QString &title, const QString &text)
{
    QTextFrameFormat formatTitle;
    formatTitle.setWidth(QTextLength(QTextLength::PercentageLength, 65));//宽度设置
    formatTitle.setPosition(QTextFrameFormat::FloatLeft);
    formatTitle.setBackground(Qt::transparent);//设置背景色
    formatTitle.setMargin(5);//设置边距
    formatTitle.setPadding(5);//设置填充
    formatTitle.setBorder(0);//设置边界宽度
    QTextFrameFormat formatContent = formatTitle;
    formatContent.setBackground(Qt::yellow);
    formatContent.setBorder(2);



    QTextCursor cursor = doc->rootFrame()->lastCursorPosition();
    cursor.insertFrame(formatTitle);
    cursor.insertText(title);
    cursor.insertFrame(formatContent);
    cursor.insertText(text);
}

void MainWindow::insertRightFrame(QTextDocument *doc, const QString &title, const QString &text)
{
    QTextFrameFormat formatTitle;
    formatTitle.setWidth(QTextLength(QTextLength::PercentageLength, 65));//宽度设置
    formatTitle.setPosition(QTextFrameFormat::FloatRight);
    formatTitle.setBackground(Qt::transparent);//设置背景色
    formatTitle.setMargin(5);//设置边距
    formatTitle.setPadding(5);//设置填充
    formatTitle.setBorder(0);//设置边界宽度
    QTextFrameFormat formatContent = formatTitle;
    formatContent.setBackground(Qt::green);
    formatContent.setBorder(2);



    QTextCursor cursor = doc->rootFrame()->lastCursorPosition();
    cursor.insertFrame(formatTitle);
    ui->textEdit_show->setTextCursor(cursor);
    ui->textEdit_show->setAlignment(Qt::AlignRight);
    cursor.insertText(title);
    cursor.insertFrame(formatContent);
    cursor.insertText(text);
}

void MainWindow::on_pushButton_refresh_clicked()
{
    emit sendRefreshFriendList();
}


void MainWindow::on_pushButton_createGroup_clicked()
{
    emit gotoCreateGroup();
}

void MainWindow::treeItemClicked(QTreeWidgetItem *item, int column)
{
    qDebug()<<"clicked"<<endl<<item->text(column);
    emit getInfo(item->text(column));
}


void MainWindow::on_pushButton_deletefriend_clicked()
{
    emit gotoDeleteFriend(ui->label_userInfo_OID->text());
}

void MainWindow::on_pushButton_blockfriend_clicked()
{
    emit gotoBlockFriend(ui->label_userInfo_OID->text(), "黑名单");
}

//void MainWindow::deleteFriend(QString ID)
//{
//    ui->label_userInfo_OID->clear();
//    ui->textEdit_userInfo->clear();
//    for (int i = 0; i < ui->treeWidget_friend->topLevelItemCount(); ++i)
//    {
//        QTreeWidgetItem *group = ui->treeWidget_friend->topLevelItem(i);
//        if(group->text(0) == "我的好友")
//        {
//            for (int j = 0; j < group->childCount(); ++j) {
//                QTreeWidgetItem *friend2 = group->child(i);
//                if(friend2->text(0) == ID)
//                {
//                    delete friend2;
//                    break;
//                }
//            }
//        }
//    }
//}

void MainWindow::on_pushButton_changegroup_clicked()
{
    emit gotoChangeGroup();//
    emit giveOID(ui->label_userInfo_OID->text());
}
