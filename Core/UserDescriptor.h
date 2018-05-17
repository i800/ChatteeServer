#ifndef _USER_DESCRIPTOR_
#define _USER_DESCRIPTOR_
#include <QObject>

class QTcpSocket;
class User;

class UserDescriptor : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* _tcpSocket;
    User* _userData;
public:
    UserDescriptor();
    UserDescriptor(QTcpSocket* tcpSocket = 0, User* userData = 0);
    UserDescriptor(const UserDescriptor&);
    UserDescriptor& operator=(const UserDescriptor&);
    ~UserDescriptor();
    void clearMemory();
    void clearMemory() const;

    inline const QTcpSocket* const tcpSocket() const { return _tcpSocket; }
    inline const User* const user() const { return _userData; }

    inline QTcpSocket* tcpSocket() { return _tcpSocket; }
    inline User* user() { return _userData; }
};

#endif
