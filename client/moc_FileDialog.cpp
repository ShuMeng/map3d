/****************************************************************************
** Meta object code from reading C++ file 'FileDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "FileDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileDialog_t {
    QByteArrayData data[5];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileDialog_t qt_meta_stringdata_FileDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FileDialog"
QT_MOC_LITERAL(1, 11, 22), // "on_applyButton_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(4, 59, 27) // "on_newSurfaceButton_clicked"

    },
    "FileDialog\0on_applyButton_clicked\0\0"
    "on_cancelButton_clicked\0"
    "on_newSurfaceButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileDialog[] = {

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

void FileDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileDialog *_t = static_cast<FileDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_applyButton_clicked(); break;
        case 1: _t->on_cancelButton_clicked(); break;
        case 2: _t->on_newSurfaceButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject FileDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileDialog.data,
      qt_meta_data_FileDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FileDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::FileDialog"))
        return static_cast< Ui::FileDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int FileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_FileDialogWidget_t {
    QByteArrayData data[20];
    char stringdata0[475];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileDialogWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileDialogWidget_t qt_meta_stringdata_FileDialogWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FileDialogWidget"
QT_MOC_LITERAL(1, 17, 31), // "on_geomLineEdit_editingFinished"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 30), // "on_geomIndexComboBox_activated"
QT_MOC_LITERAL(4, 81, 4), // "text"
QT_MOC_LITERAL(5, 86, 31), // "on_dataLineEdit_editingFinished"
QT_MOC_LITERAL(6, 118, 30), // "on_dataIndexComboBox_activated"
QT_MOC_LITERAL(7, 149, 33), // "on_startFrameSpinBox_valueCha..."
QT_MOC_LITERAL(8, 183, 1), // "i"
QT_MOC_LITERAL(9, 185, 31), // "on_endFrameSpinBox_valueChanged"
QT_MOC_LITERAL(10, 217, 27), // "on_geomBrowseButton_clicked"
QT_MOC_LITERAL(11, 245, 27), // "on_dataBrowseButton_clicked"
QT_MOC_LITERAL(12, 273, 31), // "on_channelsBrowseButton_clicked"
QT_MOC_LITERAL(13, 305, 32), // "on_leadlinksBrowseButton_clicked"
QT_MOC_LITERAL(14, 338, 31), // "on_fiducialBrowseButton_clicked"
QT_MOC_LITERAL(15, 370, 32), // "on_landmarksBrowseButton_clicked"
QT_MOC_LITERAL(16, 403, 25), // "on_geomSaveButton_clicked"
QT_MOC_LITERAL(17, 429, 23), // "on_expandButton_clicked"
QT_MOC_LITERAL(18, 453, 11), // "updateFiles"
QT_MOC_LITERAL(19, 465, 9) // "updateRMS"

    },
    "FileDialogWidget\0on_geomLineEdit_editingFinished\0"
    "\0on_geomIndexComboBox_activated\0text\0"
    "on_dataLineEdit_editingFinished\0"
    "on_dataIndexComboBox_activated\0"
    "on_startFrameSpinBox_valueChanged\0i\0"
    "on_endFrameSpinBox_valueChanged\0"
    "on_geomBrowseButton_clicked\0"
    "on_dataBrowseButton_clicked\0"
    "on_channelsBrowseButton_clicked\0"
    "on_leadlinksBrowseButton_clicked\0"
    "on_fiducialBrowseButton_clicked\0"
    "on_landmarksBrowseButton_clicked\0"
    "on_geomSaveButton_clicked\0"
    "on_expandButton_clicked\0updateFiles\0"
    "updateRMS"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileDialogWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    1,   95,    2, 0x0a /* Public */,
       5,    0,   98,    2, 0x0a /* Public */,
       6,    1,   99,    2, 0x0a /* Public */,
       7,    1,  102,    2, 0x0a /* Public */,
       9,    1,  105,    2, 0x0a /* Public */,
      10,    0,  108,    2, 0x0a /* Public */,
      11,    0,  109,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    0,  115,    2, 0x0a /* Public */,
      18,    0,  116,    2, 0x0a /* Public */,
      19,    0,  117,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void FileDialogWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileDialogWidget *_t = static_cast<FileDialogWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_geomLineEdit_editingFinished(); break;
        case 1: _t->on_geomIndexComboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_dataLineEdit_editingFinished(); break;
        case 3: _t->on_dataIndexComboBox_activated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_startFrameSpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_endFrameSpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_geomBrowseButton_clicked(); break;
        case 7: _t->on_dataBrowseButton_clicked(); break;
        case 8: _t->on_channelsBrowseButton_clicked(); break;
        case 9: _t->on_leadlinksBrowseButton_clicked(); break;
        case 10: _t->on_fiducialBrowseButton_clicked(); break;
        case 11: _t->on_landmarksBrowseButton_clicked(); break;
        case 12: _t->on_geomSaveButton_clicked(); break;
        case 13: _t->on_expandButton_clicked(); break;
        case 14: { bool _r = _t->updateFiles();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->updateRMS(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileDialogWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FileDialogWidget.data,
      qt_meta_data_FileDialogWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FileDialogWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileDialogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileDialogWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::FileDialogWidget"))
        return static_cast< Ui::FileDialogWidget*>(this);
    return QWidget::qt_metacast(_clname);
}

int FileDialogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
