#ifndef _PACKET_HANDLER_
#define _PACKET_HANDLER_
#include <QObject>

class PacketHandler : public QObject
{
    Q_OBJECT
private:
    PacketHandler(const PacketHandler&) = delete;
    PacketHandler& operator=(const PacketHandler&) = delete;
public:

};

#endif
