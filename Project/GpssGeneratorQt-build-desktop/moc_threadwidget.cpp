/****************************************************************************
** Meta object code from reading C++ file 'threadwidget.h'
**
** Created: Mon Dec 10 15:52:32 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GpssGeneratorQt/threadwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneratorGpss__ThreadWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   29,   28,   28, 0x0a,
      48,   29,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GeneratorGpss__ThreadWidget[] = {
    "GeneratorGpss::ThreadWidget\0\0i\0"
    "typeChanged(int)\0funcChanged(int)\0"
};

const QMetaObject GeneratorGpss::ThreadWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GeneratorGpss__ThreadWidget,
      qt_meta_data_GeneratorGpss__ThreadWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneratorGpss::ThreadWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneratorGpss::ThreadWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneratorGpss::ThreadWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneratorGpss__ThreadWidget))
        return static_cast<void*>(const_cast< ThreadWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GeneratorGpss::ThreadWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: typeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: funcChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
