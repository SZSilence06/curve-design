/****************************************************************************
** Meta object code from reading C++ file 'qevent_adapter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/qt_platform/qevent_adapter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qevent_adapter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_framework__QEventAdapter_t {
    QByteArrayData data[16];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_framework__QEventAdapter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_framework__QEventAdapter_t qt_meta_stringdata_framework__QEventAdapter = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 10),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 10),
QT_MOC_LITERAL(4, 48, 13),
QT_MOC_LITERAL(5, 62, 11),
QT_MOC_LITERAL(6, 74, 8),
QT_MOC_LITERAL(7, 83, 11),
QT_MOC_LITERAL(8, 95, 3),
QT_MOC_LITERAL(9, 99, 10),
QT_MOC_LITERAL(10, 110, 11),
QT_MOC_LITERAL(11, 122, 4),
QT_MOC_LITERAL(12, 127, 10),
QT_MOC_LITERAL(13, 138, 5),
QT_MOC_LITERAL(14, 144, 14),
QT_MOC_LITERAL(15, 159, 24)
    },
    "framework::QEventAdapter\0load_model\0"
    "\0save_model\0buttonPressed\0button_name\0"
    "keyPress\0std::string\0key\0keyRelease\0"
    "send_cevent\0name\0boost::any\0param\0"
    "get_ui_handler\0osg::ref_ptr<ui_handler>\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_framework__QEventAdapter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a,
       3,    0,   50,    2, 0x0a,
       4,    1,   51,    2, 0x0a,
       6,    1,   54,    2, 0x0a,
       9,    1,   57,    2, 0x0a,
      10,    2,   60,    2, 0x0a,
      14,    0,   65,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 12,   11,   13,
    0x80000000 | 15,

       0        // eod
};

void framework::QEventAdapter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QEventAdapter *_t = static_cast<QEventAdapter *>(_o);
        switch (_id) {
        case 0: _t->load_model(); break;
        case 1: _t->save_model(); break;
        case 2: _t->buttonPressed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->keyPress((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 4: _t->keyRelease((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 5: _t->send_cevent((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const boost::any(*)>(_a[2]))); break;
        case 6: { osg::ref_ptr<ui_handler> _r = _t->get_ui_handler();
            if (_a[0]) *reinterpret_cast< osg::ref_ptr<ui_handler>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject framework::QEventAdapter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_framework__QEventAdapter.data,
      qt_meta_data_framework__QEventAdapter,  qt_static_metacall, 0, 0}
};


const QMetaObject *framework::QEventAdapter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *framework::QEventAdapter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_framework__QEventAdapter.stringdata))
        return static_cast<void*>(const_cast< QEventAdapter*>(this));
    return QObject::qt_metacast(_clname);
}

int framework::QEventAdapter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE