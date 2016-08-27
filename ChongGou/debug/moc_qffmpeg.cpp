/****************************************************************************
** Meta object code from reading C++ file 'qffmpeg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qffmpeg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qffmpeg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QFFmpeg_t {
    QByteArrayData data[11];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QFFmpeg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QFFmpeg_t qt_meta_stringdata_QFFmpeg = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QFFmpeg"
QT_MOC_LITERAL(1, 8, 8), // "GetImage"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 5), // "image"
QT_MOC_LITERAL(4, 24, 12), // "sendSavePath"
QT_MOC_LITERAL(5, 37, 8), // "savePath"
QT_MOC_LITERAL(6, 46, 10), // "updateTime"
QT_MOC_LITERAL(7, 57, 4), // "time"
QT_MOC_LITERAL(8, 62, 11), // "getSavePath"
QT_MOC_LITERAL(9, 74, 1), // "s"
QT_MOC_LITERAL(10, 76, 9) // "playLocal"

    },
    "QFFmpeg\0GetImage\0\0image\0sendSavePath\0"
    "savePath\0updateTime\0time\0getSavePath\0"
    "s\0playLocal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFFmpeg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   48,    2, 0x0a /* Public */,
      10,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::LongLong,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

       0        // eod
};

void QFFmpeg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QFFmpeg *_t = static_cast<QFFmpeg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->sendSavePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateTime((*reinterpret_cast< const qint64(*)>(_a[1]))); break;
        case 3: _t->getSavePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->playLocal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QFFmpeg::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFFmpeg::GetImage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QFFmpeg::*_t)(const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFFmpeg::sendSavePath)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QFFmpeg::*_t)(const qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFFmpeg::updateTime)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QFFmpeg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QFFmpeg.data,
      qt_meta_data_QFFmpeg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QFFmpeg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFFmpeg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QFFmpeg.stringdata0))
        return static_cast<void*>(const_cast< QFFmpeg*>(this));
    return QObject::qt_metacast(_clname);
}

int QFFmpeg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void QFFmpeg::GetImage(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QFFmpeg::sendSavePath(const QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QFFmpeg::updateTime(const qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
