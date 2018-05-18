#include "Core.h"
#include "UserDescriptor.h"
#include "Encryption/PassGenerator.h"
#include "BusinessLayer/User.h"
#include "BusinessLayer/Binding.h"
#include "BusinessLayer/Message.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <cassert>

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
    qDeleteAll(_clients.begin(), _clients.end());
}

bool Core::registerNewUser(const UserRegPacket& packet)
{
    QPair<QString, QString> passDesc =
            PassGenerator::getInstance().getEncryptedPass(packet.pass());

    User user(0, packet.username(), packet.bio(), packet.email(),
              passDesc.first, passDesc.second);

    return _dao.addUser(user);
}

bool Core::loginUser(const UserLogPacket& packet, const QTcpSocket* sender)
{
    User user = _dao.getUserByUsername(packet.username());
    QPair<QString, QString> passDesc(user.pass(), user.hashkey());
    if (user.username() == "")
    {
        return false;
    }
    else if (PassGenerator::getInstance().checkPass(passDesc, packet.pass()))
    {
        UserDescriptor* ud = find(sender);
        assert(ud);
        ud->user(&user);
        return true;
    }

    return false;
}

bool Core::addChat(const UserAddChatPacket&  packet, const QTcpSocket* sender)
{
    UserDescriptor* ud = find(sender);
    if (!ud || !ud->user()) return false;
    qint32 ida = _dao.getUserByUsername(ud->user()->username()).id();
    qint32 idb = _dao.getUserByUsername(packet.to()).id();
    Binding binding(ida, idb);
    return _dao.addBinding(binding);
}

bool Core::sendMessage(const UserAddMessPacket&  packet, const QTcpSocket* sender)
{
    UserDescriptor* ud = find(sender);
    if (!ud || !ud->user()) return false;
    qint32 ida = _dao.getUserByUsername(ud->user()->username()).id();
    qint32 idb = _dao.getUserByUsername(packet.to()).id();
    Message message(ida, idb, packet.text(), ida, QDateTime::currentSecsSinceEpoch());
    return _dao.addMessage(message);
}

QList<QString> Core::getChat(const UserGetChatPacket& packet, const QTcpSocket* sender)
{
    UserDescriptor* ud = find(sender);
    //assert(ud && ud->user());
    return _dao.getMessagesBetwUsers(ud->user()->username(), packet.to());
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

UserDescriptor* Core::find(const QTcpSocket* connection)
{
    for (UserDescriptor* i : _clients)
    {
        if (i->tcpSocket() == connection)
        {
            return i;
        }
    }

    return 0;
}

void Core::onNewConnection()
{
    QTcpSocket* pSocket = _tcpServer->nextPendingConnection();
    connect(pSocket, &QTcpSocket::readyRead, this, &Core::processMessage);
    connect(pSocket, &QTcpSocket::disconnected, this, &Core::onConnectionClosed);

    _clients << new UserDescriptor(pSocket);

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
        {
            UserRegPacket packet = _packetHandler.makeUserRegPacket(data);
            pSender->write(toCharArray(registerNewUser(packet)));
            pSender->flush();
            break;
        }
    case PacketHandler::USER_LOG:
        {
            UserLogPacket packet = _packetHandler.makeUserLogPacket(data);
            char* c = toCharArray(loginUser(packet, pSender));
            pSender->write(c);
            pSender->flush();
            break;
        }
    case PacketHandler::USER_ADD_CHAT:
        {
            UserAddChatPacket packet = _packetHandler.makeUserAddChatPacket(data);
            pSender->write(toCharArray(addChat(packet, pSender)));
            pSender->flush();
            break;
        }
    case PacketHandler::USER_ADD_MESS:
        {
            UserAddMessPacket packet = _packetHandler.makeUserAddMessPacket(data);
            pSender->write(toCharArray(sendMessage(packet, pSender)));
            pSender->flush();
            break;
        }
    case PacketHandler::USER_GET_CHAT:
        {
            UserGetChatPacket packet = _packetHandler.makeUserGetChatPacket(data);
            QByteArray arr;
            QDataStream out(&arr, QIODevice::ReadWrite);
            out << getChat(packet, pSender);
            pSender->write(arr);
            pSender->flush();
        }
    }
}

void Core::onConnectionClosed()
{
    QTcpSocket* pClient = qobject_cast<QTcpSocket*>(sender());
    if (pClient)
    {
        _clients.removeAll(find(pClient));
    }
#ifndef NDEBUG
    qDebug() << "A client disconnected";
#endif
}

char* toCharArray(const bool value)
{
    char* arr = new char[1];
    arr[0] = value ? (char)1 : (char)-1;
    return arr;
}
