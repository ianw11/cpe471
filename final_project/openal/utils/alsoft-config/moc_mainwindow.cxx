/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   31,   31,   31, 0x08,
      32,   31,   31,   31, 0x08,
      51,   31,   31,   31, 0x08,
      72,   98,   31,   31, 0x08,
     103,   31,   31,   31, 0x08,
     128,   98,   31,   31, 0x08,
     155,   31,   31,   31, 0x08,
     181,   31,   31,   31, 0x08,
     195,   31,   31,   31, 0x08,
     212,   31,   31,   31, 0x08,
     237,  268,   31,   31, 0x08,
     271,  268,   31,   31, 0x08,
     303,   98,   31,   31, 0x08,
     330,  363,   31,   31, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0saveCurrentConfig()\0\0"
    "saveConfigAsFile()\0loadConfigFromFile()\0"
    "updatePeriodSizeEdit(int)\0size\0"
    "updatePeriodSizeSlider()\0"
    "updatePeriodCountEdit(int)\0"
    "updatePeriodCountSlider()\0addHrtfFile()\0"
    "removeHrtfFile()\0updateHrtfRemoveButton()\0"
    "showEnabledBackendMenu(QPoint)\0pt\0"
    "showDisabledBackendMenu(QPoint)\0"
    "updateReverbBoostEdit(int)\0"
    "updateReverbBoostSlider(QString)\0value\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->saveCurrentConfig(); break;
        case 1: _t->saveConfigAsFile(); break;
        case 2: _t->loadConfigFromFile(); break;
        case 3: _t->updatePeriodSizeEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updatePeriodSizeSlider(); break;
        case 5: _t->updatePeriodCountEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updatePeriodCountSlider(); break;
        case 7: _t->addHrtfFile(); break;
        case 8: _t->removeHrtfFile(); break;
        case 9: _t->updateHrtfRemoveButton(); break;
        case 10: _t->showEnabledBackendMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 11: _t->showDisabledBackendMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 12: _t->updateReverbBoostEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateReverbBoostSlider((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE