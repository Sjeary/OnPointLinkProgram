/********************************************************************************
** Form generated from reading UI file 'creategroup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGROUP_H
#define UI_CREATEGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_creategroup
{
public:
    QTableWidget *createGroupList;
    QPushButton *pushButton_confirm;

    void setupUi(QWidget *creategroup)
    {
        if (creategroup->objectName().isEmpty())
            creategroup->setObjectName(QString::fromUtf8("creategroup"));
        creategroup->resize(400, 579);
        createGroupList = new QTableWidget(creategroup);
        createGroupList->setObjectName(QString::fromUtf8("createGroupList"));
        createGroupList->setGeometry(QRect(10, 60, 256, 451));
        pushButton_confirm = new QPushButton(creategroup);
        pushButton_confirm->setObjectName(QString::fromUtf8("pushButton_confirm"));
        pushButton_confirm->setGeometry(QRect(290, 280, 106, 30));

        retranslateUi(creategroup);

        QMetaObject::connectSlotsByName(creategroup);
    } // setupUi

    void retranslateUi(QWidget *creategroup)
    {
        creategroup->setWindowTitle(QApplication::translate("creategroup", "Form", nullptr));
        pushButton_confirm->setText(QApplication::translate("creategroup", "confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class creategroup: public Ui_creategroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGROUP_H
