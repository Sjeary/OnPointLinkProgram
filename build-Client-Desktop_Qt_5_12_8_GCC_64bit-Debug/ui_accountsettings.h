/********************************************************************************
** Form generated from reading UI file 'accountsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTSETTINGS_H
#define UI_ACCOUNTSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountSettings
{
public:
    QPushButton *tmpPushButton;

    void setupUi(QWidget *AccountSettings)
    {
        if (AccountSettings->objectName().isEmpty())
            AccountSettings->setObjectName(QString::fromUtf8("AccountSettings"));
        AccountSettings->resize(388, 167);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AccountSettings->sizePolicy().hasHeightForWidth());
        AccountSettings->setSizePolicy(sizePolicy);
        tmpPushButton = new QPushButton(AccountSettings);
        tmpPushButton->setObjectName(QString::fromUtf8("tmpPushButton"));
        tmpPushButton->setGeometry(QRect(0, 0, 391, 171));

        retranslateUi(AccountSettings);

        QMetaObject::connectSlotsByName(AccountSettings);
    } // setupUi

    void retranslateUi(QWidget *AccountSettings)
    {
        AccountSettings->setWindowTitle(QApplication::translate("AccountSettings", "\347\224\250\346\210\267\350\256\276\347\275\256", nullptr));
        tmpPushButton->setText(QApplication::translate("AccountSettings", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountSettings: public Ui_AccountSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTSETTINGS_H
