#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QTextDocument;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getMessage(QString ID, QString content);

    void addMessageItem(QString name);

signals:
    void sendMessage(QString ID, QString content);

private slots:
    void on_pushButton_input_clicked();

    void on_radioButton_message_toggled(bool checked);

    void on_radioButton_friends_toggled(bool checked);

    void on_radioButton_settings_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    void setRootFrameFormat(QTextDocument *doc);

    void insertLeftFrame(QTextDocument *doc, const QString &title, const QString &text);

    void insertRightFrame(QTextDocument *doc, const QString &title,const QString &text);
};

#endif // MAINWINDOW_H
