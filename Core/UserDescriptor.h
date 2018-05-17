#ifndef _USER_DESCRIPTOR_
#define _USER_DESCRIPTOR_
#include <QObject>

class QTcpSocket;
class User;

class UserDescriptor : public QObject
{
    Q_OBJECT
private:
    quint64* _suid;
    QTcpSocket* _tcpSocket;
    User* _userData;
public:
    UserDescriptor();
    UserDescriptor(const quint64* suid = 0, const QTcpSocket* tcpSocket = 0,
                   const User* userData = 0);
    UserDescriptor(const UserDescriptor&);
    UserDescriptor& operator=(const UserDescriptor&);
    ~UserDescriptor();

    inline const quint64* const suid() const { return _suid; }
    inline const QTcpSocket* const tcpSocket() const { return _tcpSocket; }
    inline const User* const user() const { return _userData; }

    inline quint64* suid() { return _suid; }
    inline QTcpSocket* tcpSocket() { return _tcpSocket; }
    inline User* user() { return _userData; }
};

#endif
