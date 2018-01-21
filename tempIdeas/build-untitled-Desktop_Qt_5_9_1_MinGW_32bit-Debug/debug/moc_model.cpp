/****************************************************************************
** Meta object code from reading C++ file 'model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Model_t {
    QByteArrayData data[15];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Model_t qt_meta_stringdata_Model = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Model"
QT_MOC_LITERAL(1, 6, 23), // "getListaStatFromLastObj"
QT_MOC_LITERAL(2, 30, 13), // "list<string>*"
QT_MOC_LITERAL(3, 44, 0), // ""
QT_MOC_LITERAL(4, 45, 17), // "getNumObjInMemory"
QT_MOC_LITERAL(5, 63, 13), // "setStatByName"
QT_MOC_LITERAL(6, 77, 4), // "name"
QT_MOC_LITERAL(7, 82, 5), // "value"
QT_MOC_LITERAL(8, 88, 11), // "ricycleLast"
QT_MOC_LITERAL(9, 100, 10), // "createErba"
QT_MOC_LITERAL(10, 111, 14), // "createUnguento"
QT_MOC_LITERAL(11, 126, 12), // "createPietra"
QT_MOC_LITERAL(12, 139, 15), // "createCristallo"
QT_MOC_LITERAL(13, 155, 10), // "createOsso"
QT_MOC_LITERAL(14, 166, 13) // "createAmuleto"

    },
    "Model\0getListaStatFromLastObj\0"
    "list<string>*\0\0getNumObjInMemory\0"
    "setStatByName\0name\0value\0ricycleLast\0"
    "createErba\0createUnguento\0createPietra\0"
    "createCristallo\0createOsso\0createAmuleto"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Model[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    3, 0x0a /* Public */,
       4,    0,   65,    3, 0x0a /* Public */,
       5,    2,   66,    3, 0x0a /* Public */,
       8,    0,   71,    3, 0x0a /* Public */,
       9,    0,   72,    3, 0x0a /* Public */,
      10,    0,   73,    3, 0x0a /* Public */,
      11,    0,   74,    3, 0x0a /* Public */,
      12,    0,   75,    3, 0x0a /* Public */,
      13,    0,   76,    3, 0x0a /* Public */,
      14,    0,   77,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::UInt,
    QMetaType::Bool, QMetaType::QString, QMetaType::UInt,    6,    7,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Model *_t = static_cast<Model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { list<string>* _r = _t->getListaStatFromLastObj();
            if (_a[0]) *reinterpret_cast< list<string>**>(_a[0]) = std::move(_r); }  break;
        case 1: { uint _r = _t->getNumObjInMemory();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->setStatByName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->ricycleLast();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->createErba(); break;
        case 5: _t->createUnguento(); break;
        case 6: _t->createPietra(); break;
        case 7: _t->createCristallo(); break;
        case 8: _t->createOsso(); break;
        case 9: _t->createAmuleto(); break;
        default: ;
        }
    }
}

const QMetaObject Model::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Model.data,
      qt_meta_data_Model,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Model::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Model.stringdata0))
        return static_cast<void*>(const_cast< Model*>(this));
    return QObject::qt_metacast(_clname);
}

int Model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
