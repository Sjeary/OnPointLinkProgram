/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Core_t {
    QByteArrayData data[38];
    char stringdata0[514];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core_t qt_meta_stringdata_Core = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Core"
QT_MOC_LITERAL(1, 5, 12), // "saveKeyValue"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "key"
QT_MOC_LITERAL(4, 23, 5), // "value"
QT_MOC_LITERAL(5, 29, 12), // "readKeyValue"
QT_MOC_LITERAL(6, 42, 18), // "sendConnectRequest"
QT_MOC_LITERAL(7, 61, 2), // "IP"
QT_MOC_LITERAL(8, 64, 4), // "port"
QT_MOC_LITERAL(9, 69, 19), // "sendMessageToServer"
QT_MOC_LITERAL(10, 89, 7), // "content"
QT_MOC_LITERAL(11, 97, 18), // "turnLoginToWaiting"
QT_MOC_LITERAL(12, 116, 11), // "setKeyValue"
QT_MOC_LITERAL(13, 128, 17), // "distributeMessage"
QT_MOC_LITERAL(14, 146, 20), // "toSendConnectRequest"
QT_MOC_LITERAL(15, 167, 18), // "toSendLoginRequest"
QT_MOC_LITERAL(16, 186, 2), // "ID"
QT_MOC_LITERAL(17, 189, 8), // "password"
QT_MOC_LITERAL(18, 198, 16), // "rememberPassword"
QT_MOC_LITERAL(19, 215, 9), // "autoLogin"
QT_MOC_LITERAL(20, 225, 19), // "toSendSignUpRequest"
QT_MOC_LITERAL(21, 245, 8), // "nickname"
QT_MOC_LITERAL(22, 254, 20), // "toSendGetInfoRequest"
QT_MOC_LITERAL(23, 275, 22), // "toSendAddFriendRequest"
QT_MOC_LITERAL(24, 298, 18), // "toSendFriendResult"
QT_MOC_LITERAL(25, 317, 6), // "accept"
QT_MOC_LITERAL(26, 324, 21), // "toSendMessageToFriend"
QT_MOC_LITERAL(27, 346, 7), // "message"
QT_MOC_LITERAL(28, 354, 19), // "toSendCreateRequest"
QT_MOC_LITERAL(29, 374, 12), // "memberIDList"
QT_MOC_LITERAL(30, 387, 17), // "getDocSendRequest"
QT_MOC_LITERAL(31, 405, 9), // "targetOID"
QT_MOC_LITERAL(32, 415, 4), // "path"
QT_MOC_LITERAL(33, 420, 17), // "toSendDocuMessage"
QT_MOC_LITERAL(34, 438, 8), // "filename"
QT_MOC_LITERAL(35, 447, 23), // "toSendDocuMessageBypath"
QT_MOC_LITERAL(36, 471, 21), // "writeDocFromByteArray"
QT_MOC_LITERAL(37, 493, 20) // "content_base64String"

    },
    "Core\0saveKeyValue\0\0key\0value\0readKeyValue\0"
    "sendConnectRequest\0IP\0port\0"
    "sendMessageToServer\0content\0"
    "turnLoginToWaiting\0setKeyValue\0"
    "distributeMessage\0toSendConnectRequest\0"
    "toSendLoginRequest\0ID\0password\0"
    "rememberPassword\0autoLogin\0"
    "toSendSignUpRequest\0nickname\0"
    "toSendGetInfoRequest\0toSendAddFriendRequest\0"
    "toSendFriendResult\0accept\0"
    "toSendMessageToFriend\0message\0"
    "toSendCreateRequest\0memberIDList\0"
    "getDocSendRequest\0targetOID\0path\0"
    "toSendDocuMessage\0filename\0"
    "toSendDocuMessageBypath\0writeDocFromByteArray\0"
    "content_base64String"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    1,  114,    2, 0x06 /* Public */,
       6,    2,  117,    2, 0x06 /* Public */,
       9,    1,  122,    2, 0x06 /* Public */,
      11,    0,  125,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,  126,    2, 0x0a /* Public */,
      13,    1,  131,    2, 0x0a /* Public */,
      14,    0,  134,    2, 0x0a /* Public */,
      15,    4,  135,    2, 0x0a /* Public */,
      20,    2,  144,    2, 0x0a /* Public */,
      22,    1,  149,    2, 0x0a /* Public */,
      23,    1,  152,    2, 0x0a /* Public */,
      24,    2,  155,    2, 0x0a /* Public */,
      26,    2,  160,    2, 0x0a /* Public */,
      28,    1,  165,    2, 0x0a /* Public */,
      30,    2,  168,    2, 0x0a /* Public */,
      33,    3,  173,    2, 0x0a /* Public */,
      35,    2,  180,    2, 0x0a /* Public */,
      36,    3,  185,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   16,   17,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   16,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   16,   27,
    QMetaType::Void, QMetaType::QStringList,   29,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   31,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QString,   31,   10,   34,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   31,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   32,   34,   37,

       0        // eod
};

void Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Core *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveKeyValue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->readKeyValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sendConnectRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->sendMessageToServer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->turnLoginToWaiting(); break;
        case 5: _t->setKeyValue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 6: _t->distributeMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->toSendConnectRequest(); break;
        case 8: _t->toSendLoginRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 9: _t->toSendSignUpRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->toSendGetInfoRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->toSendAddFriendRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->toSendFriendResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->toSendMessageToFriend((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->toSendCreateRequest((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 15: _t->getDocSendRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->toSendDocuMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 17: _t->toSendDocuMessageBypath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->writeDocFromByteArray((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Core::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::saveKeyValue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Core::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::readKeyValue)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Core::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::sendConnectRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Core::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::sendMessageToServer)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::turnLoginToWaiting)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Core.data,
    qt_meta_data_Core,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Core::saveKeyValue(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::readKeyValue(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::sendConnectRequest(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Core::sendMessageToServer(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Core::turnLoginToWaiting()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
