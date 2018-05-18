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
    bool loginUser(const UserLogPacket& packet, const QTcpSocket* sender);
    bool addChat(const UserAddChatPacket& packet, const QTcpSocket* sender);
    QList<QString> getChat(const UserGetChatPacket& packet, const QTcpSocket* sender);
    QList<QString> getBindings(const UserGetBngsPacket& packet, const QTcpSocket* sender);
    bool sendMessage(const UserAddMessPacket& packet, const QTcpSocket* sender);
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

char* toCharArray(const bool);

#endif
