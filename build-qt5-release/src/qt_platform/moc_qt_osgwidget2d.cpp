/****************************************************************************
** Meta object code from reading C++ file 'qt_osgwidget2d.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/qt_platform/qt_osgwidget2d.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_osgwidget2d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_framework__OSG2DWidget_t {
    QByteArrayData data[6];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_framework__OSG2DWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_framework__OSG2DWidget_t qt_meta_stringdata_framework__OSG2DWidget = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 19),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 4),
QT_MOC_LITERAL(4, 49, 12),
QT_MOC_LITERAL(5, 62, 4)
    },
    "framework::OSG2DWidget\0edit_butong_clicked\0"
    "\0falg\0on_ok_cancel\0flag\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_framework__OSG2DWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void framework::OSG2DWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OSG2DWidget *_t = static_cast<OSG2DWidget *>(_o);
        switch (_id) {
        case 0: _t->edit_butong_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ok_cancel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OSG2DWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OSG2DWidget::edit_butong_clicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject framework::OSG2DWidget::staticMetaObject = {
    { &OSGWidget::staticMetaObject, qt_meta_stringdata_framework__OSG2DWidget.data,
      qt_meta_data_framework__OSG2DWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *framework::OSG2DWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *framework::OSG2DWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_framework__OSG2DWidget.stringdata))
        return static_cast<void*>(const_cast< OSG2DWidget*>(this));
    return OSGWidget::qt_metacast(_clname);
}

int framework::OSG2DWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OSGWidget::qt_metacall(_c, _id, _a);
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
void framework::OSG2DWidget::edit_butong_clicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
