/****************************************************************************
** Meta object code from reading C++ file 'displayandslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../untitled/displayandslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'displayandslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DisplayAndSlider_t {
    QByteArrayData data[11];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayAndSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayAndSlider_t qt_meta_stringdata_DisplayAndSlider = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DisplayAndSlider"
QT_MOC_LITERAL(1, 17, 12), // "valueChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "newValue"
QT_MOC_LITERAL(4, 40, 11), // "fromDisplay"
QT_MOC_LITERAL(5, 52, 7), // "display"
QT_MOC_LITERAL(6, 60, 1), // "n"
QT_MOC_LITERAL(7, 62, 5), // "value"
QT_MOC_LITERAL(8, 68, 8), // "setValue"
QT_MOC_LITERAL(9, 77, 12), // "updateSlider"
QT_MOC_LITERAL(10, 90, 1) // "s"

    },
    "DisplayAndSlider\0valueChanged\0\0newValue\0"
    "fromDisplay\0display\0n\0value\0setValue\0"
    "updateSlider\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayAndSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a /* Public */,
       7,    0,   53,    2, 0x0a /* Public */,
       8,    1,   54,    2, 0x0a /* Public */,
       9,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void DisplayAndSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisplayAndSlider *_t = static_cast<DisplayAndSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->fromDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->display((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { int _r = _t->value();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateSlider((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DisplayAndSlider::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayAndSlider::valueChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (DisplayAndSlider::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayAndSlider::fromDisplay)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject DisplayAndSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DisplayAndSlider.data,
      qt_meta_data_DisplayAndSlider,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DisplayAndSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayAndSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayAndSlider.stringdata0))
        return static_cast<void*>(const_cast< DisplayAndSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int DisplayAndSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void DisplayAndSlider::valueChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DisplayAndSlider::fromDisplay(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
