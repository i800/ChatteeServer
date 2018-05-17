#include "UserDescriptor.h"
#include <QTcpSocket>
#include "BusinessLayer/User.h"

UserDescriptor::UserDescriptor(quint64 *suid, QTcpSocket *tcpSocket, User *userData):
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
    clearMemory();

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
    clearMemory();

#ifndef NDEBUG
    qDebug() << "An user descriptor deleted";
#endif
}

void UserDescriptor::clearMemory()
{
    delete _suid;
    delete _tcpSocket;
    delete _userData;
}

void UserDescriptor::clearMemory() const
{
    delete _suid;
    delete _tcpSocket;
    delete _userData;
}
