/********************************************************************************
** Form generated from reading UI file 'switchserverip.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITCHSERVERIP_H
#define UI_SWITCHSERVERIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SwitchServerIP
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *SwitchServerIP)
    {
        if (SwitchServerIP->objectName().isEmpty())
            SwitchServerIP->setObjectName(QString::fromUtf8("SwitchServerIP"));
        SwitchServerIP->resize(400, 200);
        verticalLayout = new QVBoxLayout(SwitchServerIP);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SwitchServerIP);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(SwitchServerIP);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(SwitchServerIP);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font1;
        font1.setPointSize(20);
        pushButton->setFont(font1);

        verticalLayout->addWidget(pushButton);


        retranslateUi(SwitchServerIP);

        QMetaObject::connectSlotsByName(SwitchServerIP);
    } // setupUi

    void retranslateUi(QWidget *SwitchServerIP)
    {
        SwitchServerIP->setWindowTitle(QApplication::translate("SwitchServerIP", "Form", nullptr));
        label->setText(QApplication::translate("SwitchServerIP", "IP:", nullptr));
        pushButton->setText(QApplication::translate("SwitchServerIP", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SwitchServerIP: public Ui_SwitchServerIP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITCHSERVERIP_H
