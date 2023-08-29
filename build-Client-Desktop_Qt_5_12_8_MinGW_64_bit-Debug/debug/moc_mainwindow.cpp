/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/front_end/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[44];
    char stringdata0[724];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 2), // "ID"
QT_MOC_LITERAL(4, 27, 7), // "content"
QT_MOC_LITERAL(5, 35, 20), // "sendAddFriendRequest"
QT_MOC_LITERAL(6, 56, 21), // "sendRefreshFriendList"
QT_MOC_LITERAL(7, 78, 13), // "gotoAddFriend"
QT_MOC_LITERAL(8, 92, 21), // "gotoDealFriendRequest"
QT_MOC_LITERAL(9, 114, 15), // "gotoCreateGroup"
QT_MOC_LITERAL(10, 130, 24), // "signal_getDocSendRequest"
QT_MOC_LITERAL(11, 155, 9), // "targetOID"
QT_MOC_LITERAL(12, 165, 4), // "path"
QT_MOC_LITERAL(13, 170, 10), // "addMessage"
QT_MOC_LITERAL(14, 181, 4), // "name"
QT_MOC_LITERAL(15, 186, 9), // "isReceive"
QT_MOC_LITERAL(16, 196, 13), // "addDocMessage"
QT_MOC_LITERAL(17, 210, 5), // "value"
QT_MOC_LITERAL(18, 216, 11), // "getUserInfo"
QT_MOC_LITERAL(19, 228, 3), // "ins"
QT_MOC_LITERAL(20, 232, 5), // "email"
QT_MOC_LITERAL(21, 238, 5), // "birth"
QT_MOC_LITERAL(22, 244, 16), // "getFriendRequest"
QT_MOC_LITERAL(23, 261, 14), // "addMessageItem"
QT_MOC_LITERAL(24, 276, 13), // "addFriendItem"
QT_MOC_LITERAL(25, 290, 17), // "changeMessageItem"
QT_MOC_LITERAL(26, 308, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(27, 325, 7), // "current"
QT_MOC_LITERAL(28, 333, 16), // "clearMessageItem"
QT_MOC_LITERAL(29, 350, 15), // "clearFriendItem"
QT_MOC_LITERAL(30, 366, 15), // "getSendFilePath"
QT_MOC_LITERAL(31, 382, 12), // "getNameByOID"
QT_MOC_LITERAL(32, 395, 3), // "OID"
QT_MOC_LITERAL(33, 399, 27), // "on_pushButton_input_clicked"
QT_MOC_LITERAL(34, 427, 30), // "on_radioButton_message_toggled"
QT_MOC_LITERAL(35, 458, 7), // "checked"
QT_MOC_LITERAL(36, 466, 30), // "on_radioButton_friends_toggled"
QT_MOC_LITERAL(37, 497, 31), // "on_radioButton_settings_toggled"
QT_MOC_LITERAL(38, 529, 31), // "on_pushButton_addFriend_clicked"
QT_MOC_LITERAL(39, 561, 35), // "on_pushButton_friendRequest_c..."
QT_MOC_LITERAL(40, 597, 33), // "on_pushButton_addThisUser_cli..."
QT_MOC_LITERAL(41, 631, 29), // "on_pushButton_refresh_clicked"
QT_MOC_LITERAL(42, 661, 33), // "on_pushButton_createGroup_cli..."
QT_MOC_LITERAL(43, 695, 28) // "on_pushButton_choDoc_clicked"

    },
    "MainWindow\0sendMessage\0\0ID\0content\0"
    "sendAddFriendRequest\0sendRefreshFriendList\0"
    "gotoAddFriend\0gotoDealFriendRequest\0"
    "gotoCreateGroup\0signal_getDocSendRequest\0"
    "targetOID\0path\0addMessage\0name\0isReceive\0"
    "addDocMessage\0value\0getUserInfo\0ins\0"
    "email\0birth\0getFriendRequest\0"
    "addMessageItem\0addFriendItem\0"
    "changeMessageItem\0QListWidgetItem*\0"
    "current\0clearMessageItem\0clearFriendItem\0"
    "getSendFilePath\0getNameByOID\0OID\0"
    "on_pushButton_input_clicked\0"
    "on_radioButton_message_toggled\0checked\0"
    "on_radioButton_friends_toggled\0"
    "on_radioButton_settings_toggled\0"
    "on_pushButton_addFriend_clicked\0"
    "on_pushButton_friendRequest_clicked\0"
    "on_pushButton_addThisUser_clicked\0"
    "on_pushButton_refresh_clicked\0"
    "on_pushButton_createGroup_clicked\0"
    "on_pushButton_choDoc_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  154,    2, 0x06 /* Public */,
       5,    1,  159,    2, 0x06 /* Public */,
       6,    0,  162,    2, 0x06 /* Public */,
       7,    0,  163,    2, 0x06 /* Public */,
       8,    0,  164,    2, 0x06 /* Public */,
       9,    0,  165,    2, 0x06 /* Public */,
      10,    2,  166,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    4,  171,    2, 0x0a /* Public */,
      16,    4,  180,    2, 0x0a /* Public */,
      18,    5,  189,    2, 0x0a /* Public */,
      22,    0,  200,    2, 0x0a /* Public */,
      23,    2,  201,    2, 0x0a /* Public */,
      24,    2,  206,    2, 0x0a /* Public */,
      25,    1,  211,    2, 0x0a /* Public */,
      28,    0,  214,    2, 0x0a /* Public */,
      29,    0,  215,    2, 0x0a /* Public */,
      30,    1,  216,    2, 0x0a /* Public */,
      31,    1,  219,    2, 0x0a /* Public */,
      33,    0,  222,    2, 0x08 /* Private */,
      34,    1,  223,    2, 0x08 /* Private */,
      36,    1,  226,    2, 0x08 /* Private */,
      37,    1,  229,    2, 0x08 /* Private */,
      38,    0,  232,    2, 0x08 /* Private */,
      39,    0,  233,    2, 0x08 /* Private */,
      40,    0,  234,    2, 0x08 /* Private */,
      41,    0,  235,    2, 0x08 /* Private */,
      42,    0,  236,    2, 0x08 /* Private */,
      43,    0,  237,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,   14,    4,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,   14,   17,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,   14,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   14,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::QString, QMetaType::QString,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sendAddFriendRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sendRefreshFriendList(); break;
        case 3: _t->gotoAddFriend(); break;
        case 4: _t->gotoDealFriendRequest(); break;
        case 5: _t->gotoCreateGroup(); break;
        case 6: _t->signal_getDocSendRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->addMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 8: _t->addDocMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 9: _t->getUserInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 10: _t->getFriendRequest(); break;
        case 11: _t->addMessageItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->addFriendItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->changeMessageItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: _t->clearMessageItem(); break;
        case 15: _t->clearFriendItem(); break;
        case 16: _t->getSendFilePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: { QString _r = _t->getNameByOID((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->on_pushButton_input_clicked(); break;
        case 19: _t->on_radioButton_message_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_radioButton_friends_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_radioButton_settings_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_pushButton_addFriend_clicked(); break;
        case 23: _t->on_pushButton_friendRequest_clicked(); break;
        case 24: _t->on_pushButton_addThisUser_clicked(); break;
        case 25: _t->on_pushButton_refresh_clicked(); break;
        case 26: _t->on_pushButton_createGroup_clicked(); break;
        case 27: _t->on_pushButton_choDoc_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendAddFriendRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendRefreshFriendList)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::gotoAddFriend)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::gotoDealFriendRequest)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::gotoCreateGroup)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signal_getDocSendRequest)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendMessage(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendAddFriendRequest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::sendRefreshFriendList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::gotoAddFriend()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::gotoDealFriendRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::gotoCreateGroup()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::signal_getDocSendRequest(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
