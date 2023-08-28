#ifndef CHOOSEDOCDIALOG_H
#define CHOOSEDOCDIALOG_H

#include <QDialog>
#include "ui_choosedocdialog.h"

namespace Ui{
    class ChooseDocDialog;
}

class ChooseDocDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDocDialog(QWidget* parent = nullptr);
    ~ChooseDocDialog();

signals:
    void signal_getFilePath(const QString path);

public slots:
    void onAccepted();

private:
    Ui::ChooseDocDialog *ui;
};

#endif // CHOOSEDOCDIALOG_H
