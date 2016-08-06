/****************************************************************************
** Meta object code from reading C++ file 'qtkJsRpcServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qtkHttpServer/qtkJsRpcServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtkJsRpcServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtkJsRpcServer_t {
    QByteArrayData data[12];
    char stringdata[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtkJsRpcServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtkJsRpcServer_t qt_meta_stringdata_QtkJsRpcServer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QtkJsRpcServer"
QT_MOC_LITERAL(1, 15, 11), // "serverError"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "error"
QT_MOC_LITERAL(4, 34, 14), // "commandExecute"
QT_MOC_LITERAL(5, 49, 9), // "commandId"
QT_MOC_LITERAL(6, 59, 6), // "params"
QT_MOC_LITERAL(7, 66, 5), // "seqId"
QT_MOC_LITERAL(8, 72, 11), // "OnServerRun"
QT_MOC_LITERAL(9, 84, 14), // "OnDisconnected"
QT_MOC_LITERAL(10, 99, 13), // "OnCommandDone"
QT_MOC_LITERAL(11, 113, 6) // "result"

    },
    "QtkJsRpcServer\0serverError\0\0error\0"
    "commandExecute\0commandId\0params\0seqId\0"
    "OnServerRun\0OnDisconnected\0OnCommandDone\0"
    "result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtkJsRpcServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    3,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   49,    2, 0x0a /* Public */,
       9,    0,   50,    2, 0x0a /* Public */,
      10,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonObject, QMetaType::Int,    5,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    5,   11,

       0        // eod
};

void QtkJsRpcServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtkJsRpcServer *_t = static_cast<QtkJsRpcServer *>(_o);
        switch (_id) {
        case 0: _t->serverError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->commandExecute((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->OnServerRun(); break;
        case 3: _t->OnDisconnected(); break;
        case 4: _t->OnCommandDone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtkJsRpcServer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtkJsRpcServer::serverError)) {
                *result = 0;
            }
        }
        {
            typedef void (QtkJsRpcServer::*_t)(int , QJsonObject , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtkJsRpcServer::commandExecute)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QtkJsRpcServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtkJsRpcServer.data,
      qt_meta_data_QtkJsRpcServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtkJsRpcServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtkJsRpcServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtkJsRpcServer.stringdata))
        return static_cast<void*>(const_cast< QtkJsRpcServer*>(this));
    return QObject::qt_metacast(_clname);
}

int QtkJsRpcServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QtkJsRpcServer::serverError(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtkJsRpcServer::commandExecute(int _t1, QJsonObject _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
