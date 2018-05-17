#include "User.h"
#include <QDebug>

User::User(const qint64 id, const QString &username, const QString &bio,
           const QString &email, const QString &pass, const QString &hashkey):
    _id(id),
    _username(username),
    _bio(bio),
    _email(email),
    _pass(pass),
    _hashkey(hashkey)
{
#ifndef NDEBUG
    qDebug() << "An user object created";
#endif
}

User::User(const User& origin):
    QObject(parent()),
    _id(origin._id),
    _username(origin._username),
    _bio(origin._bio),
    _email(origin._email),
    _pass(origin._pass),
    _hashkey(origin._hashkey)
{
#ifndef NDEBUG
    qDebug() << "An user object copied";
#endif
}

User& User::operator=(const User& origin)
{
    _id = origin._id;
    _username = origin._username;
    _bio = origin._bio;
    _email = origin._email;
    _pass = origin._pass;
    _hashkey = origin._hashkey;

#ifndef NDEBUG
    qDebug() << "An user object reassigned";
#endif

    return *this;
}

User::~User()
{
#ifndef NDEBUG
    qDebug() << "An user object deleted";
#endif
}
