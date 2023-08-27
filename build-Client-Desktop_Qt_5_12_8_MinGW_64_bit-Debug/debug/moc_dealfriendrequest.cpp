/****************************************************************************
** Meta object code from reading C++ file 'dealfriendrequest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/front_end/dealfriendrequest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dealfriendrequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DealFriendRequest_t {
    QByteArrayData data[7];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DealFriendRequest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DealFriendRequest_t qt_meta_stringdata_DealFriendRequest = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DealFriendRequest"
QT_MOC_LITERAL(1, 18, 13), // "acceptRequest"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 2), // "ID"
QT_MOC_LITERAL(4, 36, 13), // "rejectRequest"
QT_MOC_LITERAL(5, 50, 14), // "addRequestItem"
QT_MOC_LITERAL(6, 65, 8) // "nickname"

    },
    "DealFriendRequest\0acceptRequest\0\0ID\0"
    "rejectRequest\0addRequestItem\0nickname"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DealFriendRequest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    6,

       0        // eod
};

void DealFriendRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DealFriendRequest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->acceptRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->rejectRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->addRequestItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DealFriendRequest::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DealFriendRequest::acceptRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DealFriendRequest::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DealFriendRequest::rejectRequest)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DealFriendRequest::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DealFriendRequest.data,
    qt_meta_data_DealFriendRequest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DealFriendRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DealFriendRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DealFriendRequest.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DealFriendRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DealFriendRequest::acceptRequest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DealFriendRequest::rejectRequest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
