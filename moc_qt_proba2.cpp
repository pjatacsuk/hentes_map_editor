
/****************************************************************************
** Meta object code from reading C++ file 'qt_proba.h'
**
** Created: Thu Aug 23 16:19:49 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt_proba.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_proba.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qt_proba[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      24,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_qt_proba[] = {
    "qt_proba\0\0updateLabel()\0updateLabel2()\0"
};

void qt_proba::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qt_proba *_t = static_cast<qt_proba *>(_o);
        switch (_id) {
        case 0: _t->updateLabel(); break;
        case 1: _t->updateLabel2(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData qt_proba::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qt_proba::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_qt_proba,
      qt_meta_data_qt_proba, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qt_proba::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qt_proba::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qt_proba::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qt_proba))
        return static_cast<void*>(const_cast< qt_proba*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int qt_proba::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
