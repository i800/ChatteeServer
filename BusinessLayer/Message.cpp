#include "Message.h"
#include <QDebug>

Message::Message(const qint64 ida, const qint64 idb, const QString &text,
                 const qint64 from, const qint64 where):
    _ida(ida),
    _idb(idb),
    _text(text),
    _from(from),
    _where(where)
{
#ifndef NDEBUG
    qDebug() << "A message object created";
#endif
}

Message::Message(const Message& origin):
    _ida(origin._ida),
    _idb(origin._idb),
    _text(origin._text),
    _from(origin._from),
    _where(origin._where)
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
    _where = origin._where;

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
