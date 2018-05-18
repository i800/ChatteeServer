#include "UserGetBngsPacket.h"
#include <QBuffer>
#include <QDebug>

UserGetBngsPacket::UserGetBngsPacket()
{
#ifndef NDEBUG
    qDebug() << "A UserGetBngsPacket instance created";
#endif
}

UserGetBngsPacket::UserGetBngsPacket(const UserGetBngsPacket&)
{
#ifndef NDEBUG
    qDebug() << "A UserGetBngsPacket instance copied";
#endif
}

UserGetBngsPacket::~UserGetBngsPacket()
{
#ifndef NDEBUG
    qDebug() << "A UserGetBngsPacket instance deleted";
#endif
}

QByteArray UserGetBngsPacket::specificDump() const
{
    return QByteArray();
}

void UserGetBngsPacket::specificLoad(QBuffer&)
{
    return;
}

char UserGetBngsPacket::specificGetID() const
{
    return 5;
}
