#ifndef _USER_REG_PACKET_
#define _USER_REG_PACKET_
#include "../Packet.h"

class UserRegPacket : public Packet
{
    Q_OBJECT
private:
    qint32 _id;
    quint64 _userid;
    QString _username;
    QString _bio;
    QString _email;
    QString _pass;
    virtual const QByteArray specificDump() const;
    virtual const qint32 specificGetID() const;
public:
    UserRegPacket(const qint32 id, const quint64 userid, const QString& username,
                  const QString& bio, const QString& email, const QString& pass);
    ~UserRegPacket();

    inline const qint32 id() const { return _id; }
    inline const quint64 userid() const { return _userid; }
    inline const QString& username() const { return _username; }
    inline const QString& bio() const { return _bio; }
    inline const QString& email() const { return _email; }
    inline const QString& pass() const { _pass; }

    inline qint32& id() { return _id; }
    inline quint64& userid() { return _userid; }
    inline QString& username() { return _username; }
    inline QString& bio() { return _bio; }
    inline QString& email() { return _email; }
    inline QString& pass() { _pass; }
};

#endif
