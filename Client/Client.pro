QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    front_end/accountsettings.cpp \
    front_end/addfriend.cpp \
    front_end/changegroup.cpp \
    front_end/choosedocdialog.cpp \
    front_end/creategroup.cpp \
    front_end/dealfriendrequest.cpp \
    front_end/login.cpp \
    front_end/mainwindow.cpp \
    front_end/newtempgroup.cpp \
    front_end/sign_up.cpp \
    front_end/switchserverip.cpp \
    main.cpp \
    rear_end/clienttcp.cpp \
    rear_end/filesystem.cpp

HEADERS += \
    core.h \
    front_end/accountsettings.h \
    front_end/addfriend.h \
    front_end/changegroup.h \
    front_end/choosedocdialog.h \
    front_end/creategroup.h \
    front_end/dealfriendrequest.h \
    front_end/login.h \
    front_end/mainwindow.h \
    front_end/newtempgroup.h \
    front_end/sign_up.h \
    front_end/switchserverip.h \
    rear_end/clienttcp.h \
    rear_end/filesystem.h

FORMS += \
    front_end/accountsettings.ui \
    front_end/addfriend.ui \
    front_end/changegroup.ui \
    front_end/choosedocdialog.ui \
    front_end/creategroup.ui \
    front_end/dealfriendrequest.ui \
    front_end/login.ui \
    front_end/mainwindow.ui \
    front_end/newtempgroup.ui \
    front_end/sign_up.ui \
    front_end/switchserverip.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    client_res.qrc
