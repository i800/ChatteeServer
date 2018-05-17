#ifndef _PACKET_HANDLER_
#define _PACKET_HANDLER_
#include "Protocol/Packet.h"

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
        USER_REG = 1,
        USER_LOG = 2,
        USER_OUT = 3,
        USER_ADD_CHAT = 4,
        USER_ADD_MESS = 5
    };
    PacketHandler();
    ~PacketHandler();
    const bool isValidPacket(const QByteArray&);
    const Packet* makePacket(const QByteArray&);
    const PacketMeta& getPacketMeta(const ByteArray&);
};

#endif
