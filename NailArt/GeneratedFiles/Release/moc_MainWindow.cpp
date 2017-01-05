/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 4), // "load"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 5), // "reset"
QT_MOC_LITERAL(4, 23, 16), // "changeThresholdI"
QT_MOC_LITERAL(5, 40, 16), // "changeThresholdD"
QT_MOC_LITERAL(6, 57, 17), // "changeBrightnessI"
QT_MOC_LITERAL(7, 75, 17), // "changeBrightnessD"
QT_MOC_LITERAL(8, 93, 15), // "changeContrastI"
QT_MOC_LITERAL(9, 109, 15), // "changeContrastD"
QT_MOC_LITERAL(10, 125, 12), // "changeGammaI"
QT_MOC_LITERAL(11, 138, 12), // "changeGammaD"
QT_MOC_LITERAL(12, 151, 17), // "changeFilterSizeI"
QT_MOC_LITERAL(13, 169, 17), // "changeFilterSizeD"
QT_MOC_LITERAL(14, 187, 17), // "changeFilterFctrI"
QT_MOC_LITERAL(15, 205, 17), // "changeFilterFctrD"
QT_MOC_LITERAL(16, 223, 11), // "changeGauge"
QT_MOC_LITERAL(17, 235, 9), // "displayIn"
QT_MOC_LITERAL(18, 245, 10), // "displayOut"
QT_MOC_LITERAL(19, 256, 4), // "save"
QT_MOC_LITERAL(20, 261, 4) // "quit"

    },
    "MainWindow\0load\0\0reset\0changeThresholdI\0"
    "changeThresholdD\0changeBrightnessI\0"
    "changeBrightnessD\0changeContrastI\0"
    "changeContrastD\0changeGammaI\0changeGammaD\0"
    "changeFilterSizeI\0changeFilterSizeD\0"
    "changeFilterFctrI\0changeFilterFctrD\0"
    "changeGauge\0displayIn\0displayOut\0save\0"
    "quit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x0a /* Public */,
       3,    0,  110,    2, 0x0a /* Public */,
       4,    1,  111,    2, 0x0a /* Public */,
       5,    1,  114,    2, 0x0a /* Public */,
       6,    1,  117,    2, 0x0a /* Public */,
       7,    1,  120,    2, 0x0a /* Public */,
       8,    1,  123,    2, 0x0a /* Public */,
       9,    1,  126,    2, 0x0a /* Public */,
      10,    1,  129,    2, 0x0a /* Public */,
      11,    1,  132,    2, 0x0a /* Public */,
      12,    1,  135,    2, 0x0a /* Public */,
      13,    1,  138,    2, 0x0a /* Public */,
      14,    1,  141,    2, 0x0a /* Public */,
      15,    1,  144,    2, 0x0a /* Public */,
      16,    1,  147,    2, 0x0a /* Public */,
      17,    0,  150,    2, 0x0a /* Public */,
      18,    0,  151,    2, 0x0a /* Public */,
      19,    0,  152,    2, 0x09 /* Protected */,
      20,    0,  153,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->load();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->reset(); break;
        case 2: _t->changeThresholdI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeThresholdD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->changeBrightnessI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeBrightnessD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->changeContrastI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeContrastD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->changeGammaI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeGammaD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->changeFilterSizeI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->changeFilterSizeD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->changeFilterFctrI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->changeFilterFctrD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->changeGauge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->displayIn(); break;
        case 16: _t->displayOut(); break;
        case 17: _t->save(); break;
        case 18: _t->quit(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
