#include "Core.h"
#include "UserDescriptor.h"
#include "Encryption/PassGenerator.h"
#include "BusinessLayer/User.h"
#include "BusinessLayer/Message.h"
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

bool Core::sendMessage(const UserAddMessPacket& packet)
{
    // TODO: change this
    quint32 ida(3);
    qint32 idb = _dao.getUserByUsername(packet.to()).id();
    Message message(ida, idb, packet.text(), ida, QDateTime::currentSecsSinceEpoch());
    return _dao.addMessage(message);
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
    qDebug() << _packetHandler.getPacketMeta(data);
    switch (_packetHandler.getPacketMeta(data))
    {
    case PacketHandler::USER_REG:
        {
            UserRegPacket packet = _packetHandler.makeUserRegPacket(data);
            pSender->write(registerNewUser(packet) ? "ok" : "error");
            break;
        }
    case PacketHandler::USER_ADD_MESS:
        {
            UserAddMessPacket packet = _packetHandler.makeUserAddMessPacket(data);
            pSender->write(sendMessage(packet) ? "ok" : "error");
            break;
        }
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

