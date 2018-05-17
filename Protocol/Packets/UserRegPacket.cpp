#include "UserRegPacket.h"
#include <QDebug>

UserRegPacket::UserRegPacket(const qint32 id, const quint64 userid,
                             const QString &username, const QString &bio,
                             const QString &email, const QString &pass):
    _id(id),
    _userid(userid),
    _username(username),
    _bio(bio),
    _email(email),
    _pass(pass)
{
#ifndef NDEBUG
    qDebug() << "A UserRegPacket instance created";
#endif
}

UserRegPacket::~UserRegPacket()
{
#ifndef NDEBUG
    qDebug() << "A UserRegPacket instance deleted";
#endif
}

const QByteArray UserRegPacket::specificDump() const
{
    QByteArray data;
    const char* username(_username.toStdString().c_str());
    const char* bio(_bio.toStdString().c_str());
    const char* email(_email.toStdString().c_str());
    const char* pass(_pass.toStdString().c_str());
    data.append((char*)&_userid, sizeof(_userid));
    data.append(username, sizeof(username));
    data.append(bio, sizeof(bio));
    data.append(email, sizeof(email));
    data.append(pass, sizeof(pass));
    return data;
}

const qint32 UserRegPacket::specificGetID() const
{
    return qint32(1);
}
