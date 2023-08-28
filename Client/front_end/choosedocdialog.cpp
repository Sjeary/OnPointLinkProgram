#include "choosedocdialog.h"

ChooseDocDialog::ChooseDocDialog(QWidget *parent) :
    QDialog(parent),ui(new Ui::ChooseDocDialog)
{
    ui->setupUi(this);
    connect(ui->checkButton,&QDialogButtonBox::accepted,this,&ChooseDocDialog::onAccepted);
}

ChooseDocDialog::~ChooseDocDialog()
{
    delete ui;
}

void ChooseDocDialog::onAccepted() {
    emit signal_getFilePath(ui->pathText->text());
}
