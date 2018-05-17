#ifndef _MESSAGE_
#define _MESSAGE_
#include <QObject>

class Message : public QObject
{
    Q_OBJECT
private:
    qint32 _ida;
    qint32 _idb;
    QString _text;
    qint32 _from;
    qint64 _when;
public:
    Message() {}
    Message(const qint32 ida, const qint32 idb, const QString& text,
            const qint32 from, const qint64 when);
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    inline qint32 ida() const { return _ida; }
    inline qint32 idb() const { return _idb; }
    inline const QString text() const { return _text; }
    inline qint32 from() const { return _from; }
    inline qint64 when() const { return _when; }

    inline qint32& ida() { return _ida; }
    inline qint32& idb() { return _idb; }
    inline QString& text() { return _text; }
    inline qint32& from() { return _from; }
    inline qint64& when() { return _when; }
};

#endif
