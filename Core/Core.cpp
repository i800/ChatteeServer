#include "Core.h"
#include "UserDescriptor.h"
#include "Encryption/PassGenerator.h"
#include "BusinessLayer/User.h"
#include "Protocol/Packets/UserRegPacket.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>

Core::Core():
    _tcpServer(new QTcpServer())
{
#ifndef NDEBUG
    qDebug() << "The core created";
#endif
}

Core::~Core()
{
#ifndef NDEBUG
    qDebug() << "The core deleted";
#endif
    _tcpServer->close();
    delete _tcpServer;
    QList<UserDescriptor*> toDelete = _clients.values();
    qDeleteAll(toDelete.begin(), toDelete.end());
}

bool Core::registerNewUser(const UserRegPacket& packet)
{
    QPair<QString, QString> passDesc =
            PassGenerator::getInstance().getEncryptedPass(packet.pass());

    User user(0, packet.username(), packet.bio(), packet.email(),
              passDesc.first, passDesc.second);

    return _dao.addUser(user);
}

void Core::start(const quint16 port)
{
    _dao.initDB();

    if (!_tcpServer->listen(QHostAddress::Any, port))
    {
        throw _tcpServer->serverError();
    }
    else
    {
#ifndef NDEBUG
    qDebug() << "The server started";
#endif
    connect(_tcpServer, &QTcpServer::newConnection,
            this, &Core::onNewConnection);
    }
}

void Core::onNewConnection()
{
    QTcpSocket* pSocket = _tcpServer->nextPendingConnection();
    connect(pSocket, &QTcpSocket::readyRead, this, &Core::processMessage);
    connect(pSocket, &QTcpSocket::disconnected, this, &Core::onConnectionClosed);

    QList<quint32> presentSUIDs = _clients.keys();
    _clients.insert(generateUniqueSUID(presentSUIDs), new UserDescriptor(pSocket));
#ifndef NDEBUG
    qDebug() << "A client connected";
#endif
}

void Core::processMessage()
{
    QTcpSocket* pSender = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = pSender->readAll();
    switch (_packetHandler.getPacketMeta(data))
    {
    case PacketHandler::USER_REG:
        UserRegPacket packet = _packetHandler.makeUserRegPacket(data);
        pSender->write(registerNewUser(packet) ? "ok" : "error");
        break;
    }
}

void Core::onConnectionClosed()
{
    QTcpSocket* pClient = qobject_cast<QTcpSocket*>(sender());
    if (pClient)
    {
        // TODO remove client
    }
#ifndef NDEBUG
    qDebug() << "A client disconnected";
#endif
}

quint32 generateUniqueSUID(const QList<quint32>& presentSUIDs)
{
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    quint32 rSUID(0);

    do
    {
        rSUID = quint32(qrand());
    } while (presentSUIDs.contains(rSUID));

    return rSUID;
}

