/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sign_up
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *picture;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_nickname;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_confirmPassword;
    QLabel *label_nickname;
    QLabel *label_password;
    QLabel *label_confirmPassword;
    QPushButton *pushButton_signUp;

    void setupUi(QWidget *sign_up)
    {
        if (sign_up->objectName().isEmpty())
            sign_up->setObjectName(QString::fromUtf8("sign_up"));
        sign_up->resize(400, 407);
        verticalLayout = new QVBoxLayout(sign_up);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        picture = new QLabel(sign_up);
        picture->setObjectName(QString::fromUtf8("picture"));

        verticalLayout->addWidget(picture);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lineEdit_nickname = new QLineEdit(sign_up);
        lineEdit_nickname->setObjectName(QString::fromUtf8("lineEdit_nickname"));
        QFont font;
        font.setPointSize(15);
        lineEdit_nickname->setFont(font);
        lineEdit_nickname->setStyleSheet(QString::fromUtf8("margin : 20px 0px"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_nickname);

        lineEdit_password = new QLineEdit(sign_up);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setFont(font);
        lineEdit_password->setStyleSheet(QString::fromUtf8("margin : 30px 0px"));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_password);

        lineEdit_confirmPassword = new QLineEdit(sign_up);
        lineEdit_confirmPassword->setObjectName(QString::fromUtf8("lineEdit_confirmPassword"));
        lineEdit_confirmPassword->setFont(font);
        lineEdit_confirmPassword->setStyleSheet(QString::fromUtf8("margin : 20px 0px"));
        lineEdit_confirmPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_confirmPassword);

        label_nickname = new QLabel(sign_up);
        label_nickname->setObjectName(QString::fromUtf8("label_nickname"));
        label_nickname->setFont(font);
        label_nickname->setStyleSheet(QString::fromUtf8("margin : 20px 0px"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_nickname);

        label_password = new QLabel(sign_up);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setFont(font);
        label_password->setStyleSheet(QString::fromUtf8("margin : 30px 0px"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_password);

        label_confirmPassword = new QLabel(sign_up);
        label_confirmPassword->setObjectName(QString::fromUtf8("label_confirmPassword"));
        label_confirmPassword->setFont(font);
        label_confirmPassword->setStyleSheet(QString::fromUtf8("margin : 20px 0px"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_confirmPassword);


        verticalLayout->addLayout(formLayout);

        pushButton_signUp = new QPushButton(sign_up);
        pushButton_signUp->setObjectName(QString::fromUtf8("pushButton_signUp"));
        QFont font1;
        font1.setPointSize(20);
        pushButton_signUp->setFont(font1);
        pushButton_signUp->setStyleSheet(QString::fromUtf8("margin : 20px 0px"));

        verticalLayout->addWidget(pushButton_signUp);


        retranslateUi(sign_up);

        QMetaObject::connectSlotsByName(sign_up);
    } // setupUi

    void retranslateUi(QWidget *sign_up)
    {
        sign_up->setWindowTitle(QApplication::translate("sign_up", "Sign up", nullptr));
        picture->setText(QApplication::translate("sign_up", "...", nullptr));
        label_nickname->setText(QApplication::translate("sign_up", "Nickname", nullptr));
        label_password->setText(QApplication::translate("sign_up", "Password", nullptr));
        label_confirmPassword->setText(QApplication::translate("sign_up", "Confirm\n"
"Password", nullptr));
        pushButton_signUp->setText(QApplication::translate("sign_up", "Sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign_up: public Ui_sign_up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
