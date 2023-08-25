#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextFrame>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setRootFrameFormat(ui->textEdit_show->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getMessage(QString ID, QString content)
{

}

void MainWindow::addMessageItem(QString ID, QString name)
{
    ui->listWidget_message->addItem(name);
}

void MainWindow::addFriendItem(QString ID, QString name)
{

}

void MainWindow::on_pushButton_input_clicked()
{
    QString text = ui->plainTextEdit_input->toPlainText();
    ui->plainTextEdit_input->clear();

    insertLeftFrame(ui->textEdit_show->document(),"me", text);

    insertRightFrame(ui->textEdit_show->document(),"me", text);

}

void MainWindow::on_pushButton_addFriend_clicked()
{
    emit gotoAddFriend();
}

void MainWindow::on_pushButton_friendRequest_clicked()
{
    emit gotoDealFriendRequest();
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
