#ifndef _CORE_
#define _CORE_
#include <QObject>
#include <QMap>
#include "Database/DAO.h"
#include "Protocol/PacketHandler.h"

class QTcpServer;
class UserDescriptor;
class UserRegPacket;

class Core : public QObject
{
    Q_OBJECT
private:
    QTcpServer* _tcpServer;
    QMap<quint32, UserDescriptor*> _clients;
    DAO _dao;
    PacketHandler _packetHandler;
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
    bool registerNewUser(const UserRegPacket&);
    bool sendMessage(const UserAddMessPacket&);
public:
    Core();
    ~Core();
    void start(const quint16 port = 45654);
private slots:
    //slot for Core
    void onNewConnection();
    //slots for clients
    void processMessage();
    void onConnectionClosed();
};

quint32 generateUniqueSUID(const QList<quint32>&);

#endif
