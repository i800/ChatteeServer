#ifndef _CORE_
#define _CORE_
#include <QObject>
#include <QMap>
#include "Database/DAO.h"
#include "Protocol/PacketHandler.h"

class QTcpServer;
class QTcpSocket;
class UserDescriptor;

class Core : public QObject
{
    Q_OBJECT
private:
    QTcpServer* _tcpServer;
    QList<UserDescriptor*> _clients;
    DAO _dao;
    PacketHandler _packetHandler;
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
    bool registerNewUser(const UserRegPacket&);
    bool loginUser(const UserLogPacket&);
    bool addChat(const UserAddChatPacket&);
    bool sendMessage(const UserAddMessPacket&);
    UserDescriptor* find(const QTcpSocket*);
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

#endif
