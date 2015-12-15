/****************************************************************************
** Meta object code from reading C++ file 'rtreeapp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../rtreeapp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtreeapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RtreeApp_t {
    QByteArrayData data[15];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RtreeApp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RtreeApp_t qt_meta_stringdata_RtreeApp = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RtreeApp"
QT_MOC_LITERAL(1, 9, 15), // "handleBlockView"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 23), // "handleAddRealEstateForm"
QT_MOC_LITERAL(4, 50, 24), // "handleEditRealEstateForm"
QT_MOC_LITERAL(5, 75, 24), // "handleFindRealEstateForm"
QT_MOC_LITERAL(6, 100, 26), // "handleRemoveRealEstateForm"
QT_MOC_LITERAL(7, 127, 14), // "handleGenerate"
QT_MOC_LITERAL(8, 142, 19), // "handleAddCoordinate"
QT_MOC_LITERAL(9, 162, 24), // "handleExitCoordinateForm"
QT_MOC_LITERAL(10, 187, 24), // "handleOpenCoordinateForm"
QT_MOC_LITERAL(11, 212, 19), // "handleAddRealEstate"
QT_MOC_LITERAL(12, 232, 25), // "handleCancelAddRealEstate"
QT_MOC_LITERAL(13, 258, 26), // "handleCancelFindRealEstate"
QT_MOC_LITERAL(14, 285, 20) // "handleFindRealEstate"

    },
    "RtreeApp\0handleBlockView\0\0"
    "handleAddRealEstateForm\0"
    "handleEditRealEstateForm\0"
    "handleFindRealEstateForm\0"
    "handleRemoveRealEstateForm\0handleGenerate\0"
    "handleAddCoordinate\0handleExitCoordinateForm\0"
    "handleOpenCoordinateForm\0handleAddRealEstate\0"
    "handleCancelAddRealEstate\0"
    "handleCancelFindRealEstate\0"
    "handleFindRealEstate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RtreeApp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RtreeApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RtreeApp *_t = static_cast<RtreeApp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleBlockView(); break;
        case 1: _t->handleAddRealEstateForm(); break;
        case 2: _t->handleEditRealEstateForm(); break;
        case 3: _t->handleFindRealEstateForm(); break;
        case 4: _t->handleRemoveRealEstateForm(); break;
        case 5: _t->handleGenerate(); break;
        case 6: _t->handleAddCoordinate(); break;
        case 7: _t->handleExitCoordinateForm(); break;
        case 8: _t->handleOpenCoordinateForm(); break;
        case 9: _t->handleAddRealEstate(); break;
        case 10: _t->handleCancelAddRealEstate(); break;
        case 11: _t->handleCancelFindRealEstate(); break;
        case 12: _t->handleFindRealEstate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RtreeApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RtreeApp.data,
      qt_meta_data_RtreeApp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RtreeApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RtreeApp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RtreeApp.stringdata0))
        return static_cast<void*>(const_cast< RtreeApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RtreeApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
