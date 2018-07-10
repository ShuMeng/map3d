/****************************************************************************
** Meta object code from reading C++ file 'dialogs.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialogs.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogs.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SizeWidget_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SizeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SizeWidget_t qt_meta_stringdata_SizeWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SizeWidget"
QT_MOC_LITERAL(1, 11, 7), // "clicked"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13) // "doubleClicked"

    },
    "SizeWidget\0clicked\0\0doubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SizeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SizeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SizeWidget *_t = static_cast<SizeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->doubleClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizeWidget::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SizeWidget::doubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SizeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SizeWidget.data,
      qt_meta_data_SizeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SizeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SizeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SizeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SizeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SizeWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SizeWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_SizePicker_t {
    QByteArrayData data[5];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SizePicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SizePicker_t qt_meta_stringdata_SizePicker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SizePicker"
QT_MOC_LITERAL(1, 11, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 22), // "on_closeButton_clicked"
QT_MOC_LITERAL(4, 59, 12) // "sizeSelected"

    },
    "SizePicker\0on_cancelButton_clicked\0\0"
    "on_closeButton_clicked\0sizeSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SizePicker[] = {

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

void SizePicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SizePicker *_t = static_cast<SizePicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cancelButton_clicked(); break;
        case 1: _t->on_closeButton_clicked(); break;
        case 2: _t->sizeSelected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SizePicker::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SizePicker.data,
      qt_meta_data_SizePicker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SizePicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SizePicker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SizePicker.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SizePicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_ColorWidget_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColorWidget_t qt_meta_stringdata_ColorWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ColorWidget"
QT_MOC_LITERAL(1, 12, 7), // "clicked"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13) // "doubleClicked"

    },
    "ColorWidget\0clicked\0\0doubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ColorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ColorWidget *_t = static_cast<ColorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->doubleClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ColorWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorWidget::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ColorWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorWidget::doubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ColorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ColorWidget.data,
      qt_meta_data_ColorWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ColorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ColorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ColorWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ColorWidget::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ColorPicker_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColorPicker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColorPicker_t qt_meta_stringdata_ColorPicker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ColorPicker"
QT_MOC_LITERAL(1, 12, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "on_closeButton_clicked"
QT_MOC_LITERAL(4, 60, 13) // "colorSelected"

    },
    "ColorPicker\0on_cancelButton_clicked\0"
    "\0on_closeButton_clicked\0colorSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColorPicker[] = {

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

void ColorPicker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ColorPicker *_t = static_cast<ColorPicker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cancelButton_clicked(); break;
        case 1: _t->on_closeButton_clicked(); break;
        case 2: _t->colorSelected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ColorPicker::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ColorPicker.data,
      qt_meta_data_ColorPicker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ColorPicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColorPicker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColorPicker.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ColorPicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
