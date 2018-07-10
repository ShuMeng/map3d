/****************************************************************************
** Meta object code from reading C++ file 'FidDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FidDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FidDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FidDialogWidget_t {
    QByteArrayData data[5];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FidDialogWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FidDialogWidget_t qt_meta_stringdata_FidDialogWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FidDialogWidget"
QT_MOC_LITERAL(1, 16, 9), // "pickColor"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "pickSize"
QT_MOC_LITERAL(4, 36, 13) // "applySettings"

    },
    "FidDialogWidget\0pickColor\0\0pickSize\0"
    "applySettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FidDialogWidget[] = {

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
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FidDialogWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FidDialogWidget *_t = static_cast<FidDialogWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pickColor(); break;
        case 1: _t->pickSize(); break;
        case 2: _t->applySettings(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject FidDialogWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FidDialogWidget.data,
      qt_meta_data_FidDialogWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FidDialogWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FidDialogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FidDialogWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::FidDialogWidget"))
        return static_cast< Ui::FidDialogWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int FidDialogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_FidDialog_t {
    QByteArrayData data[4];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FidDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FidDialog_t qt_meta_stringdata_FidDialog = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FidDialog"
QT_MOC_LITERAL(1, 10, 22), // "on_applyButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23) // "on_cancelButton_clicked"

    },
    "FidDialog\0on_applyButton_clicked\0\0"
    "on_cancelButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FidDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FidDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FidDialog *_t = static_cast<FidDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_applyButton_clicked(); break;
        case 1: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject FidDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FidDialog.data,
      qt_meta_data_FidDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FidDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FidDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FidDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::FidDialog"))
        return static_cast< Ui::FidDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int FidDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
