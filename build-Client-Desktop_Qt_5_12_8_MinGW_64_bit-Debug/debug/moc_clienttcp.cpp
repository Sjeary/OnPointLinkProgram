/****************************************************************************
** Meta object code from reading C++ file 'clienttcp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/rear_end/clienttcp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clienttcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientTcp_t {
    QByteArrayData data[11];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientTcp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientTcp_t qt_meta_stringdata_ClientTcp = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ClientTcp"
QT_MOC_LITERAL(1, 10, 10), // "getConnect"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "connectFailed"
QT_MOC_LITERAL(4, 36, 17), // "sendMessageFailed"
QT_MOC_LITERAL(5, 54, 10), // "getMessage"
QT_MOC_LITERAL(6, 65, 7), // "content"
QT_MOC_LITERAL(7, 73, 10), // "tryConnect"
QT_MOC_LITERAL(8, 84, 2), // "IP"
QT_MOC_LITERAL(9, 87, 4), // "port"
QT_MOC_LITERAL(10, 92, 13) // "toSendMessage"

    },
    "ClientTcp\0getConnect\0\0connectFailed\0"
    "sendMessageFailed\0getMessage\0content\0"
    "tryConnect\0IP\0port\0toSendMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientTcp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   50,    2, 0x0a /* Public */,
      10,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::QByteArray,    6,

       0        // eod
};

void ClientTcp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientTcp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getConnect(); break;
        case 1: _t->connectFailed(); break;
        case 2: _t->sendMessageFailed(); break;
        case 3: _t->getMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->tryConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->toSendMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientTcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTcp::getConnect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientTcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTcp::connectFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientTcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTcp::sendMessageFailed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientTcp::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTcp::getMessage)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientTcp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ClientTcp.data,
    qt_meta_data_ClientTcp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientTcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientTcp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientTcp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientTcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ClientTcp::getConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientTcp::connectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientTcp::sendMessageFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ClientTcp::getMessage(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
