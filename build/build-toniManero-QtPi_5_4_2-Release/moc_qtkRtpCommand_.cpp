/****************************************************************************
** Meta object code from reading C++ file 'qtkRtpCommand_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qtkHttpServer/qtkRtpCommand_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkRtpCommand_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_qtkRtpCommand__t {
    QByteArrayData data[8];
    char stringdata[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qtkRtpCommand__t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qtkRtpCommand__t qt_meta_stringdata_qtkRtpCommand_ = {
    {
QT_MOC_LITERAL(0, 0, 14), // "qtkRtpCommand_"
QT_MOC_LITERAL(1, 15, 11), // "commandDone"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "commandId"
QT_MOC_LITERAL(4, 38, 6), // "result"
QT_MOC_LITERAL(5, 45, 16), // "OnCommandExecute"
QT_MOC_LITERAL(6, 62, 6), // "params"
QT_MOC_LITERAL(7, 69, 5) // "seqId"

    },
    "qtkRtpCommand_\0commandDone\0\0commandId\0"
    "result\0OnCommandExecute\0params\0seqId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qtkRtpCommand_[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject, QMetaType::Int,    3,    6,    7,

       0        // eod
};

void qtkRtpCommand_::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        qtkRtpCommand_ *_t = static_cast<qtkRtpCommand_ *>(_o);
        switch (_id) {
        case 0: _t->commandDone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->OnCommandExecute((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (qtkRtpCommand_::*_t)(int , QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&qtkRtpCommand_::commandDone)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject qtkRtpCommand_::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_qtkRtpCommand_.data,
      qt_meta_data_qtkRtpCommand_,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *qtkRtpCommand_::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qtkRtpCommand_::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_qtkRtpCommand_.stringdata))
        return static_cast<void*>(const_cast< qtkRtpCommand_*>(this));
    return QObject::qt_metacast(_clname);
}

int qtkRtpCommand_::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void qtkRtpCommand_::commandDone(int _t1, QByteArray _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
