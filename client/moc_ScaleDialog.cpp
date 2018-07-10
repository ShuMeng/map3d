/****************************************************************************
** Meta object code from reading C++ file 'ScaleDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ScaleDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScaleDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScaleDialog_t {
    QByteArrayData data[6];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScaleDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScaleDialog_t qt_meta_stringdata_ScaleDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ScaleDialog"
QT_MOC_LITERAL(1, 12, 12), // "rangeToggled"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "checked"
QT_MOC_LITERAL(4, 34, 15), // "functionToggled"
QT_MOC_LITERAL(5, 50, 14) // "mappingToggled"

    },
    "ScaleDialog\0rangeToggled\0\0checked\0"
    "functionToggled\0mappingToggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScaleDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    1,   32,    2, 0x08 /* Private */,
       5,    1,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void ScaleDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScaleDialog *_t = static_cast<ScaleDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rangeToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->functionToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->mappingToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScaleDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ScaleDialog.data,
      qt_meta_data_ScaleDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScaleDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScaleDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScaleDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::ScaleDialog"))
        return static_cast< Ui::ScaleDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int ScaleDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
