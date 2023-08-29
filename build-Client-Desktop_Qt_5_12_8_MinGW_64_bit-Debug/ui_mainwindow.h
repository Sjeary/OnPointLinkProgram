/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *sideFrame;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *picture;
    QRadioButton *radioButton_message;
    QRadioButton *radioButton_friends;
    QRadioButton *radioButton_settings;
    QRadioButton *radioButton;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget_middle;
    QWidget *page_mid_0;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget_message;
    QWidget *page_mid_1;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_searchUser;
    QPushButton *pushButton_addFriend;
    QPushButton *pushButton_refresh;
    QPushButton *pushButton_friendRequest;
    QPushButton *pushButton_createGroup;
    QListWidget *listWidget_friend;
    QWidget *page_mid_2;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QStackedWidget *stackedWidget_main;
    QWidget *page_main_0;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit_show;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_choDoc;
    QPushButton *pushButton_input;
    QPlainTextEdit *plainTextEdit_input;
    QWidget *page_main_1;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_userInfo_OID;
    QTextEdit *textEdit_userInfo;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_addThisUser;
    QWidget *page_main_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(901, 589);
        horizontalLayout = new QHBoxLayout(MainWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sideFrame = new QFrame(MainWindow);
        sideFrame->setObjectName(QString::fromUtf8("sideFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sideFrame->sizePolicy().hasHeightForWidth());
        sideFrame->setSizePolicy(sizePolicy);
        sideFrame->setMinimumSize(QSize(50, 0));
        sideFrame->setFrameShape(QFrame::StyledPanel);
        sideFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(sideFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(sideFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(20);
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        picture = new QLabel(sideFrame);
        picture->setObjectName(QString::fromUtf8("picture"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(picture->sizePolicy().hasHeightForWidth());
        picture->setSizePolicy(sizePolicy1);
        picture->setMinimumSize(QSize(45, 45));
        picture->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(picture);

        radioButton_message = new QRadioButton(sideFrame);
        radioButton_message->setObjectName(QString::fromUtf8("radioButton_message"));
        radioButton_message->setChecked(true);

        verticalLayout->addWidget(radioButton_message);

        radioButton_friends = new QRadioButton(sideFrame);
        radioButton_friends->setObjectName(QString::fromUtf8("radioButton_friends"));

        verticalLayout->addWidget(radioButton_friends);

        radioButton_settings = new QRadioButton(sideFrame);
        radioButton_settings->setObjectName(QString::fromUtf8("radioButton_settings"));

        verticalLayout->addWidget(radioButton_settings);

        radioButton = new QRadioButton(sideFrame);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(sideFrame);

        stackedWidget_middle = new QStackedWidget(MainWindow);
        stackedWidget_middle->setObjectName(QString::fromUtf8("stackedWidget_middle"));
        stackedWidget_middle->setMinimumSize(QSize(300, 0));
        stackedWidget_middle->setFrameShape(QFrame::StyledPanel);
        page_mid_0 = new QWidget();
        page_mid_0->setObjectName(QString::fromUtf8("page_mid_0"));
        verticalLayout_2 = new QVBoxLayout(page_mid_0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listWidget_message = new QListWidget(page_mid_0);
        listWidget_message->setObjectName(QString::fromUtf8("listWidget_message"));
        listWidget_message->setFont(font);

        verticalLayout_2->addWidget(listWidget_message);

        stackedWidget_middle->addWidget(page_mid_0);
        page_mid_1 = new QWidget();
        page_mid_1->setObjectName(QString::fromUtf8("page_mid_1"));
        verticalLayout_4 = new QVBoxLayout(page_mid_1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_searchUser = new QLineEdit(page_mid_1);
        lineEdit_searchUser->setObjectName(QString::fromUtf8("lineEdit_searchUser"));

        horizontalLayout_3->addWidget(lineEdit_searchUser);

        pushButton_addFriend = new QPushButton(page_mid_1);
        pushButton_addFriend->setObjectName(QString::fromUtf8("pushButton_addFriend"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_addFriend->sizePolicy().hasHeightForWidth());
        pushButton_addFriend->setSizePolicy(sizePolicy2);
        pushButton_addFriend->setStyleSheet(QString::fromUtf8("padding : 5px 10px"));

        horizontalLayout_3->addWidget(pushButton_addFriend);

        pushButton_refresh = new QPushButton(page_mid_1);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));
        pushButton_refresh->setStyleSheet(QString::fromUtf8("padding : 5px 10px"));

        horizontalLayout_3->addWidget(pushButton_refresh);


        verticalLayout_4->addLayout(horizontalLayout_3);

        pushButton_friendRequest = new QPushButton(page_mid_1);
        pushButton_friendRequest->setObjectName(QString::fromUtf8("pushButton_friendRequest"));

        verticalLayout_4->addWidget(pushButton_friendRequest);

        pushButton_createGroup = new QPushButton(page_mid_1);
        pushButton_createGroup->setObjectName(QString::fromUtf8("pushButton_createGroup"));

        verticalLayout_4->addWidget(pushButton_createGroup);

        listWidget_friend = new QListWidget(page_mid_1);
        listWidget_friend->setObjectName(QString::fromUtf8("listWidget_friend"));

        verticalLayout_4->addWidget(listWidget_friend);

        stackedWidget_middle->addWidget(page_mid_1);
        page_mid_2 = new QWidget();
        page_mid_2->setObjectName(QString::fromUtf8("page_mid_2"));
        verticalLayout_6 = new QVBoxLayout(page_mid_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        radioButton_2 = new QRadioButton(page_mid_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_6->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(page_mid_2);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout_6->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(page_mid_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout_6->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(page_mid_2);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        verticalLayout_6->addWidget(radioButton_5);

        stackedWidget_middle->addWidget(page_mid_2);

        horizontalLayout->addWidget(stackedWidget_middle);

        stackedWidget_main = new QStackedWidget(MainWindow);
        stackedWidget_main->setObjectName(QString::fromUtf8("stackedWidget_main"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(5);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(stackedWidget_main->sizePolicy().hasHeightForWidth());
        stackedWidget_main->setSizePolicy(sizePolicy3);
        stackedWidget_main->setFrameShape(QFrame::StyledPanel);
        page_main_0 = new QWidget();
        page_main_0->setObjectName(QString::fromUtf8("page_main_0"));
        verticalLayout_3 = new QVBoxLayout(page_main_0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        textEdit_show = new QTextEdit(page_main_0);
        textEdit_show->setObjectName(QString::fromUtf8("textEdit_show"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(5);
        sizePolicy4.setHeightForWidth(textEdit_show->sizePolicy().hasHeightForWidth());
        textEdit_show->setSizePolicy(sizePolicy4);
        textEdit_show->setReadOnly(true);

        verticalLayout_3->addWidget(textEdit_show);

        widget = new QWidget(page_main_0);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_choDoc = new QPushButton(widget);
        pushButton_choDoc->setObjectName(QString::fromUtf8("pushButton_choDoc"));

        horizontalLayout_2->addWidget(pushButton_choDoc);

        pushButton_input = new QPushButton(widget);
        pushButton_input->setObjectName(QString::fromUtf8("pushButton_input"));

        horizontalLayout_2->addWidget(pushButton_input);


        verticalLayout_3->addWidget(widget);

        plainTextEdit_input = new QPlainTextEdit(page_main_0);
        plainTextEdit_input->setObjectName(QString::fromUtf8("plainTextEdit_input"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(2);
        sizePolicy5.setHeightForWidth(plainTextEdit_input->sizePolicy().hasHeightForWidth());
        plainTextEdit_input->setSizePolicy(sizePolicy5);

        verticalLayout_3->addWidget(plainTextEdit_input);

        stackedWidget_main->addWidget(page_main_0);
        page_main_1 = new QWidget();
        page_main_1->setObjectName(QString::fromUtf8("page_main_1"));
        verticalLayout_5 = new QVBoxLayout(page_main_1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_userInfo_OID = new QLabel(page_main_1);
        label_userInfo_OID->setObjectName(QString::fromUtf8("label_userInfo_OID"));

        verticalLayout_5->addWidget(label_userInfo_OID);

        textEdit_userInfo = new QTextEdit(page_main_1);
        textEdit_userInfo->setObjectName(QString::fromUtf8("textEdit_userInfo"));

        verticalLayout_5->addWidget(textEdit_userInfo);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton = new QPushButton(page_main_1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        pushButton_3 = new QPushButton(page_main_1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_addThisUser = new QPushButton(page_main_1);
        pushButton_addThisUser->setObjectName(QString::fromUtf8("pushButton_addThisUser"));

        horizontalLayout_4->addWidget(pushButton_addThisUser);


        verticalLayout_5->addLayout(horizontalLayout_4);

        stackedWidget_main->addWidget(page_main_1);
        page_main_2 = new QWidget();
        page_main_2->setObjectName(QString::fromUtf8("page_main_2"));
        verticalLayout_7 = new QVBoxLayout(page_main_2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_2 = new QLabel(page_main_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_7->addWidget(label_2);

        stackedWidget_main->addWidget(page_main_2);

        horizontalLayout->addWidget(stackedWidget_main);


        retranslateUi(MainWindow);

        stackedWidget_middle->setCurrentIndex(1);
        stackedWidget_main->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OnPointLink ", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "OP", nullptr));
        picture->setText(QApplication::translate("MainWindow", "...", nullptr));
        radioButton_message->setText(QApplication::translate("MainWindow", "M", nullptr));
        radioButton_friends->setText(QApplication::translate("MainWindow", "F", nullptr));
        radioButton_settings->setText(QApplication::translate("MainWindow", "S", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "N", nullptr));
        pushButton_addFriend->setText(QApplication::translate("MainWindow", "+", nullptr));
        pushButton_refresh->setText(QApplication::translate("MainWindow", "Ref", nullptr));
        pushButton_friendRequest->setText(QApplication::translate("MainWindow", "Friend request", nullptr));
        pushButton_createGroup->setText(QApplication::translate("MainWindow", "Create group", nullptr));
        radioButton_2->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        radioButton_3->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        radioButton_4->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        radioButton_5->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        pushButton_choDoc->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_input->setText(QApplication::translate("MainWindow", "OK", nullptr));
        label_userInfo_OID->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_addThisUser->setText(QApplication::translate("MainWindow", "Add", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
