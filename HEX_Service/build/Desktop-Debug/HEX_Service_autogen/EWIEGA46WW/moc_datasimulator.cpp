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
    QByteArrayData data[14];
    char stringdata0[120];
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
QT_MOC_LITERAL(5, 43, 4), // "next"
QT_MOC_LITERAL(6, 48, 17), // "const ServoFrame*"
QT_MOC_LITERAL(7, 66, 8), // "logError"
QT_MOC_LITERAL(8, 75, 3), // "msg"
QT_MOC_LITERAL(9, 79, 5), // "reset"
QT_MOC_LITERAL(10, 85, 13), // "qualitySample"
QT_MOC_LITERAL(11, 99, 4), // "rssi"
QT_MOC_LITERAL(12, 104, 3), // "per"
QT_MOC_LITERAL(13, 108, 11) // "onTimerTick"

    },
    "DataSimulator\0frameReady\0\0ServoFrame\0"
    "frame\0next\0const ServoFrame*\0logError\0"
    "msg\0reset\0qualitySample\0rssi\0per\0"
    "onTimerTick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataSimulator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       7,    1,   48,    2, 0x06 /* Public */,
       9,    0,   51,    2, 0x06 /* Public */,
      10,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    0x80000000 | 6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   11,   12,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DataSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataSimulator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< const ServoFrame(*)>(_a[1]))); break;
        case 1: { const ServoFrame* _r = _t->next();
            if (_a[0]) *reinterpret_cast< const ServoFrame**>(_a[0]) = std::move(_r); }  break;
        case 2: _t->logError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->reset(); break;
        case 4: _t->qualitySample((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->onTimerTick(); break;
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
            using _t = const ServoFrame * (DataSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::next)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::logError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::reset)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataSimulator::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSimulator::qualitySample)) {
                *result = 4;
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
void DataSimulator::frameReady(const ServoFrame & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
const ServoFrame * DataSimulator::next()
{
    const ServoFrame* _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
void DataSimulator::logError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataSimulator::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DataSimulator::qualitySample(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
