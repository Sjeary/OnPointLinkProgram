/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/front_end/login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Login_t {
    QByteArrayData data[22];
    char stringdata0[334];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Login_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Login_t qt_meta_stringdata_Login = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Login"
QT_MOC_LITERAL(1, 6, 10), // "gotoSignUp"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 18), // "gotoSwitchServerIP"
QT_MOC_LITERAL(4, 37, 17), // "reconnectToServer"
QT_MOC_LITERAL(5, 55, 9), // "sendLogin"
QT_MOC_LITERAL(6, 65, 2), // "ID"
QT_MOC_LITERAL(7, 68, 8), // "password"
QT_MOC_LITERAL(8, 77, 16), // "rememberPassword"
QT_MOC_LITERAL(9, 94, 9), // "autoLogin"
QT_MOC_LITERAL(10, 104, 21), // "writeSavedAccountInfo"
QT_MOC_LITERAL(11, 126, 8), // "savedOID"
QT_MOC_LITERAL(12, 135, 13), // "savedPassword"
QT_MOC_LITERAL(13, 149, 17), // "connectedToServer"
QT_MOC_LITERAL(14, 167, 13), // "cannotConnect"
QT_MOC_LITERAL(15, 181, 12), // "loginSuccess"
QT_MOC_LITERAL(16, 194, 11), // "loginFailed"
QT_MOC_LITERAL(17, 206, 3), // "log"
QT_MOC_LITERAL(18, 210, 28), // "on_pushButton_SignUp_clicked"
QT_MOC_LITERAL(19, 239, 36), // "on_pushButton_switchServerIP_..."
QT_MOC_LITERAL(20, 276, 27), // "on_pushButton_Login_clicked"
QT_MOC_LITERAL(21, 304, 29) // "on_pushButton_connect_clicked"

    },
    "Login\0gotoSignUp\0\0gotoSwitchServerIP\0"
    "reconnectToServer\0sendLogin\0ID\0password\0"
    "rememberPassword\0autoLogin\0"
    "writeSavedAccountInfo\0savedOID\0"
    "savedPassword\0connectedToServer\0"
    "cannotConnect\0loginSuccess\0loginFailed\0"
    "log\0on_pushButton_SignUp_clicked\0"
    "on_pushButton_switchServerIP_clicked\0"
    "on_pushButton_Login_clicked\0"
    "on_pushButton_connect_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Login[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    4,   87,    2, 0x06 /* Public */,
      10,    2,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  101,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    1,  104,    2, 0x0a /* Public */,
      16,    0,  107,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  108,    2, 0x08 /* Private */,
      19,    0,  109,    2, 0x08 /* Private */,
      20,    0,  110,    2, 0x08 /* Private */,
      21,    0,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Login *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gotoSignUp(); break;
        case 1: _t->gotoSwitchServerIP(); break;
        case 2: _t->reconnectToServer(); break;
        case 3: _t->sendLogin((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 4: _t->writeSavedAccountInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->connectedToServer(); break;
        case 6: _t->cannotConnect(); break;
        case 7: _t->loginSuccess(); break;
        case 8: _t->loginFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->loginFailed(); break;
        case 10: _t->on_pushButton_SignUp_clicked(); break;
        case 11: _t->on_pushButton_switchServerIP_clicked(); break;
        case 12: _t->on_pushButton_Login_clicked(); break;
        case 13: _t->on_pushButton_connect_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Login::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Login::gotoSignUp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Login::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Login::gotoSwitchServerIP)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Login::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Login::reconnectToServer)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Login::*)(QString , QString , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Login::sendLogin)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Login::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Login::writeSavedAccountInfo)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Login::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Login.data,
    qt_meta_data_Login,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Login.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Login::gotoSignUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Login::gotoSwitchServerIP()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Login::reconnectToServer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Login::sendLogin(QString _t1, QString _t2, bool _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Login::writeSavedAccountInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
