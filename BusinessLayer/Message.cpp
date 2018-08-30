#include "Message.h"
#include <QDebug>

Message::Message(const qint32 ida, const qint32 idb, const QString &text,
                 const qint32 from, const qint64 when):
    _ida(ida),
    _idb(idb),
    _text(text),
    _from(from),
    _when(when)
{
#ifndef NDEBUG
    qDebug() << "A message object created";
#endif
}

Message::Message(const Message& origin):
    QObject(parent()),
    _ida(origin._ida),
    _idb(origin._idb),
    _text(origin._text),
    _from(origin._from),
    _when(origin._when)
{
#ifndef NDEBUG
    qDebug() << "A message object copied";
#endif
}

Message& Message::operator=(const Message& origin)
{
    _ida = origin._ida;
    _idb = origin._idb;
    _text = origin._text;
    _from = origin._from;
    _when = origin._when;

#ifndef NDEBUG
    qDebug() << "A message object reassigned";
#endif

    return *this;
}

Message::~Message()
{
#ifndef NDEBUG
    qDebug() << "A message object deleted";
#endif
}
