#include "UserDescriptor.h"
#include <QTcpSocket>
#include "BusinessLayer/User.h"

UserDescriptor::UserDescriptor(const quint64 *suid, const QTcpSocket *tcpSocket,
                               const User *userData):
    _suid(suid),
    _tcpSocket(tcpSocket),
    _userData(userData)
{
#ifndef NDEBUG
    qDebug() << "An user descriptor created";
#endif
}

UserDescriptor::UserDescriptor(const UserDescriptor& origin):
    _suid(origin._suid),
    _tcpSocket(origin._tcpSocket),
    _userData(origin._userData)
{
#ifndef NDEBUG
    qDebug() << "An user descriptor copied";
#endif
}

UserDescriptor& UserDescriptor::operator=(const UserDescriptor& origin)
{
    _suid = origin._suid;
    _tcpSocket = origin._tcpSocket;
    _userData = origin._userData;

#ifndef NDEBUG
    qDebug() << "An user descriptor reassigned";
#endif

    return *this;
}

UserDescriptor::~UserDescriptor()
{
    delete _suid;
    delete _tcpSocket;
    delete _userData;

#ifndef NDEBUG
    qDebug() << "An user descriptor deleted";
#endif
}
