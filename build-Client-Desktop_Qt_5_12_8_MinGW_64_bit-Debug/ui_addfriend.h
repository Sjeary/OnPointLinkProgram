/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriend
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_ID;
    QRadioButton *radioButton_name;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_input;
    QPushButton *pushButton_search;
    QListWidget *listWidget;

    void setupUi(QWidget *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName(QString::fromUtf8("AddFriend"));
        AddFriend->resize(400, 500);
        verticalLayout = new QVBoxLayout(AddFriend);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_ID = new QRadioButton(AddFriend);
        radioButton_ID->setObjectName(QString::fromUtf8("radioButton_ID"));

        horizontalLayout->addWidget(radioButton_ID);

        radioButton_name = new QRadioButton(AddFriend);
        radioButton_name->setObjectName(QString::fromUtf8("radioButton_name"));

        horizontalLayout->addWidget(radioButton_name);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_input = new QLineEdit(AddFriend);
        lineEdit_input->setObjectName(QString::fromUtf8("lineEdit_input"));

        horizontalLayout_2->addWidget(lineEdit_input);

        pushButton_search = new QPushButton(AddFriend);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));

        horizontalLayout_2->addWidget(pushButton_search);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(AddFriend);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);


        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QWidget *AddFriend)
    {
        AddFriend->setWindowTitle(QApplication::translate("AddFriend", "Add friend", nullptr));
        radioButton_ID->setText(QApplication::translate("AddFriend", "OID", nullptr));
        radioButton_name->setText(QApplication::translate("AddFriend", "Nickname", nullptr));
        pushButton_search->setText(QApplication::translate("AddFriend", "search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
