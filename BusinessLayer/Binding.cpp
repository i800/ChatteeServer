#include "Binding.h"
#include <QDebug>

Binding::Binding(const qint64 ida, const qint64 idb):
    _ida(ida),
    _idb(idb)
{
#ifndef NDEBUG
    qDebug() << "A binding object created";
#endif
}

Binding::Binding(const Binding& origin):
    _ida(origin._ida),
    _idb(origin._idb)
{
#ifndef NDEBUG
    qDebug() << "A binding object copied";
#endif
}

Binding& Binding::operator=(const Binding& origin)
{
    _ida = origin._ida;
    _idb = origin._idb;

#ifndef NDEBUG
    qDebug() << "A binding object reassigned";
#endif

    return *this;
}

Binding::~Binding()
{
#ifndef NDEBUG
    qDebug() << "A binding object deleted";
#endif
}
