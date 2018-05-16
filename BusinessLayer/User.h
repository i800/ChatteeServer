#ifndef _USER_
#define _USER_
#include <QObject>

class User : public QObject
{
    Q_OBJECT
private:
    qint64 _id;
    QString _username;
    QString _bio;
    QString _email;
    QString _pass;
    QString _hashkey;
public:
    User();
    User(const qint64 id, const QString& username, const QString& bio,
         const QString& email, const QString& pass, const QString& hashkey);
    User(const User&);
    User operator=(const User&);
    ~User();

    inline const qint64 id() { return _id; }
    inline const QString username() { return _username; }
    inline const QString bio() { return _bio; }
    inline const QString email() { return _email; }
    inline const QString pass() { return _pass; }
    inline const QString hashkey() { return _hashkey; }

    inline qint64& id() { return _id; }
    inline QString& username() { return _username; }
    inline QString& bio() { return _bio; }
    inline QString& email() { return _email; }
    inline QString& pass() { return _pass; }
    inline QString& hashkey() { return _hashkey; }
};

#endif
