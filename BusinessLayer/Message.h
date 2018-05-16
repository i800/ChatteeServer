#ifndef _MESSAGE_
#define _MESSAGE_
#include <QObject>

class Message : public QObject
{
    Q_OBJECT
private:
    qint64 _ida;
    qint64 _idb;
    QString _text;
    qint64 _from;
    qint64 _where;
public:
    Message() {}
    Message(const qint64 ida, const qint64 idb, const QString& text,
            const qint64 from, const qint64 where);
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    inline const qint64 ida() { return _ida; }
    inline const qint64 idb() { return _idb; }
    inline const QString text() { return _text; }
    inline const qint64 from() { return _from; }
    inline const qint64 where() { return _where; }

    inline qint64& ida() { return _ida; }
    inline qint64& idb() { return _idb; }
    inline QString& text() { return _text; }
    inline qint64& from() { return _from; }
    inline qint64& where() { return _where; }
};

#endif
