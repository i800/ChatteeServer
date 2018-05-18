#ifndef _PACKET_HANDLER_
#define _PACKET_HANDLER_
#include "Protocol/Packets/UserRegPacket.h"
#include "Protocol/Packets/UserLogPacket.h"
#include "Protocol/Packets/UserAddChatPacket.h"
#include "Protocol/Packets/UserAddMessPacket.h"
#include "Protocol/Packets/UserGetChatPacket.h"
#include "Protocol/Packets/UserGetBngsPacket.h"

class PacketHandler : public QObject
{
    Q_OBJECT
private:
    PacketHandler(const PacketHandler&) = delete;
    PacketHandler& operator=(const PacketHandler&) = delete;
public:
    // Packet id equals to index in the enum.
    enum PacketMeta
    {
        USER_REG,
        USER_LOG,
        USER_ADD_CHAT,
        USER_ADD_MESS,
        USER_GET_CHAT,
        USER_GET_BNGS
    };
    PacketHandler();
    ~PacketHandler();
    bool isValidPacket(const QByteArray&);
    UserRegPacket makeUserRegPacket(QByteArray&);
    UserLogPacket makeUserLogPacket(QByteArray&);
    UserAddChatPacket makeUserAddChatPacket(QByteArray&);
    UserAddMessPacket makeUserAddMessPacket(QByteArray&);
    UserGetChatPacket makeUserGetChatPacket(QByteArray&);
    UserGetBngsPacket makeUserGetBngsPacket(QByteArray&);
    PacketMeta getPacketMeta(const QByteArray&);
    quint16 getPacketSize(const QByteArray&);
};

#endif
