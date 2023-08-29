/********************************************************************************
** Form generated from reading UI file 'choosedocdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEDOCDIALOG_H
#define UI_CHOOSEDOCDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseDocDialog
{
public:
    QDialogButtonBox *checkButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *pathText;

    void setupUi(QDialog *ChooseDocDialog)
    {
        if (ChooseDocDialog->objectName().isEmpty())
            ChooseDocDialog->setObjectName(QString::fromUtf8("ChooseDocDialog"));
        ChooseDocDialog->resize(400, 199);
        checkButton = new QDialogButtonBox(ChooseDocDialog);
        checkButton->setObjectName(QString::fromUtf8("checkButton"));
        checkButton->setGeometry(QRect(30, 140, 341, 32));
        checkButton->setOrientation(Qt::Horizontal);
        checkButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(ChooseDocDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 351, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        pathText = new QLineEdit(verticalLayoutWidget);
        pathText->setObjectName(QString::fromUtf8("pathText"));

        verticalLayout->addWidget(pathText);


        retranslateUi(ChooseDocDialog);
        QObject::connect(checkButton, SIGNAL(accepted()), ChooseDocDialog, SLOT(accept()));
        QObject::connect(checkButton, SIGNAL(rejected()), ChooseDocDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseDocDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseDocDialog)
    {
        ChooseDocDialog->setWindowTitle(QApplication::translate("ChooseDocDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("ChooseDocDialog", "\350\257\267\350\276\223\345\205\245Linux\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseDocDialog: public Ui_ChooseDocDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEDOCDIALOG_H
