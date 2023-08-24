/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_picture;
    QHBoxLayout *horizontalLayout;
    QLabel *label_userID;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_password;
    QLineEdit *lineEdit;
    QCheckBox *checkBox_rememberPassword;
    QCheckBox *checkBox_autoLogin;
    QPushButton *pushButton_Login;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_SignUp;
    QPushButton *pushButton_switchServerIP;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(400, 600);
        verticalLayout = new QVBoxLayout(login);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_picture = new QLabel(login);
        label_picture->setObjectName(QString::fromUtf8("label_picture"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_picture->sizePolicy().hasHeightForWidth());
        label_picture->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_picture);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_userID = new QLabel(login);
        label_userID->setObjectName(QString::fromUtf8("label_userID"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_userID->sizePolicy().hasHeightForWidth());
        label_userID->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(15);
        label_userID->setFont(font);
        label_userID->setStyleSheet(QString::fromUtf8("margin : 30px 0px"));

        horizontalLayout->addWidget(label_userID);

        comboBox = new QComboBox(login);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);
        comboBox->setFont(font);
        comboBox->setEditable(true);

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_password = new QLabel(login);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        sizePolicy1.setHeightForWidth(label_password->sizePolicy().hasHeightForWidth());
        label_password->setSizePolicy(sizePolicy1);
        label_password->setFont(font);
        label_password->setStyleSheet(QString::fromUtf8("margin : 30px 0px"));

        horizontalLayout_2->addWidget(label_password);

        lineEdit = new QLineEdit(login);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setFont(font);
        lineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        checkBox_rememberPassword = new QCheckBox(login);
        checkBox_rememberPassword->setObjectName(QString::fromUtf8("checkBox_rememberPassword"));

        verticalLayout->addWidget(checkBox_rememberPassword);

        checkBox_autoLogin = new QCheckBox(login);
        checkBox_autoLogin->setObjectName(QString::fromUtf8("checkBox_autoLogin"));

        verticalLayout->addWidget(checkBox_autoLogin);

        pushButton_Login = new QPushButton(login);
        pushButton_Login->setObjectName(QString::fromUtf8("pushButton_Login"));
        QFont font1;
        font1.setPointSize(20);
        pushButton_Login->setFont(font1);
        pushButton_Login->setStyleSheet(QString::fromUtf8("margin : 30px 0px"));

        verticalLayout->addWidget(pushButton_Login);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_SignUp = new QPushButton(login);
        pushButton_SignUp->setObjectName(QString::fromUtf8("pushButton_SignUp"));
        pushButton_SignUp->setStyleSheet(QString::fromUtf8("margin : 20px 0px;\n"
"border : 0px;"));

        horizontalLayout_3->addWidget(pushButton_SignUp);

        pushButton_switchServerIP = new QPushButton(login);
        pushButton_switchServerIP->setObjectName(QString::fromUtf8("pushButton_switchServerIP"));
        pushButton_switchServerIP->setStyleSheet(QString::fromUtf8("margin : 20px 0px;\n"
"border : 0px;"));

        horizontalLayout_3->addWidget(pushButton_switchServerIP);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Login", nullptr));
        label_picture->setText(QApplication::translate("login", "...", nullptr));
        label_userID->setText(QApplication::translate("login", "User ID:", nullptr));
        label_password->setText(QApplication::translate("login", "Password:", nullptr));
        checkBox_rememberPassword->setText(QApplication::translate("login", "remember password", nullptr));
        checkBox_autoLogin->setText(QApplication::translate("login", "auto-login", nullptr));
        pushButton_Login->setText(QApplication::translate("login", "Login", nullptr));
        pushButton_SignUp->setText(QApplication::translate("login", "Sign up", nullptr));
        pushButton_switchServerIP->setText(QApplication::translate("login", "Switch server IP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
