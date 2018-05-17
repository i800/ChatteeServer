#ifndef _BINDING_
#define _BINDING_
#include <QObject>

class Binding : public QObject
{
    Q_OBJECT
private:
    qint64 _ida;
    qint64 _idb;
public:
    Binding() {}
    Binding(const qint64 ida, const qint64 idb);
    Binding(const Binding&);
    Binding& operator=(const Binding&);
    ~Binding();

    inline qint64 ida() const { return _ida; }
    inline qint64 idb() const { return _idb; }
    inline qint64& ida() { return _ida; }
    inline qint64& idb() { return _idb; }
};

#endif
