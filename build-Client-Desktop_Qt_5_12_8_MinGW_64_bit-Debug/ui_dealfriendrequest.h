/********************************************************************************
** Form generated from reading UI file 'dealfriendrequest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEALFRIENDREQUEST_H
#define UI_DEALFRIENDREQUEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DealFriendRequest
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *DealFriendRequest)
    {
        if (DealFriendRequest->objectName().isEmpty())
            DealFriendRequest->setObjectName(QString::fromUtf8("DealFriendRequest"));
        DealFriendRequest->resize(400, 600);
        verticalLayout = new QVBoxLayout(DealFriendRequest);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(DealFriendRequest);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QFont font;
        font.setPointSize(15);
        listWidget->setFont(font);

        verticalLayout->addWidget(listWidget);


        retranslateUi(DealFriendRequest);

        QMetaObject::connectSlotsByName(DealFriendRequest);
    } // setupUi

    void retranslateUi(QWidget *DealFriendRequest)
    {
        DealFriendRequest->setWindowTitle(QApplication::translate("DealFriendRequest", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DealFriendRequest: public Ui_DealFriendRequest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEALFRIENDREQUEST_H
