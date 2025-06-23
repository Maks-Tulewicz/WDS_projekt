/****************************************************************************
** Meta object code from reading C++ file 'datasimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../datasimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datasimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataSimulator_t {
    QByteArrayData data[15];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataSimulator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataSimulator_t qt_meta_stringdata_DataSimulator = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DataSimulator"
QT_MOC_LITERAL(1, 14, 10), // "frameReady"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "ServoFrame"
QT_MOC_LITERAL(4, 37, 5), // "frame"
QT_MOC_LITERAL(5, 43, 8), // "logError"
QT_MOC_LITERAL(6, 52, 3), // "msg"
QT_MOC_LITERAL(7, 56, 10), // "logMessage"
QT_MOC_LITERAL(8, 67, 23), // "disconnectedDueToErrors"
QT_MOC_LITERAL(9, 91, 5), // "reset"
QT_MOC_LITERAL(10, 97, 13), // "qualitySample"
QT_MOC_LITERAL(11, 111, 4), // "rssi"
QT_MOC_LITERAL(12, 116, 3), // "per"
QT_MOC_LITERAL(13, 120, 11), // "onTimerTick"
QT_MOC_LITERAL(14, 132, 15) // "onExternalFrame"

    },
    "DataSimulator\0frameReady\0\0ServoFrame\0"
    "frame\0logError\0msg\0logMessage\0"
    "disconnectedDueToErrors\0reset\0"
    "qualitySample\0rssi\0per\0onTimerTick\0"
    "onExternalFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataSimulator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       8,    0,   63,    2, 0x06 /* Public */,
       9,    0,   64,    2, 0x06 /* Public */,
      10,    2,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   70,    2, 0x08 /* Private */,
      14,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void DataSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataSimulator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< const ServoFrame(*)>(_a[1]))); break;
        case 1: _t->logError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->logMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->disconnectedDueToErrors(); break;
        case 4: _t->reset(); break;
        case 5: _t->qualitySample((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->onTimerTick(); break;
        case 7: _t->onExternalFrame((*reinterpret_cast< const ServoFrame(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataSimulator::*)(const ServoFrame & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::frameReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::logError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::logMessage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::disconnectedDueToErrors)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::reset)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::qualitySample)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataSimulator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataSimulator.data,
    qt_meta_data_DataSimulator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataSimulator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DataSimulator::frameReady(const ServoFrame & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataSimulator::logError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataSimulator::logMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataSimulator::disconnectedDueToErrors()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DataSimulator::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DataSimulator::qualitySample(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
