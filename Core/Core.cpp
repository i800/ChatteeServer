#include "Core.h"
#include "UserDescriptor.h"
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
    QByteArray message = pSender->readAll();
    qDebug() << message.count();
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

const quint32 generateUniqueSUID(const QList<quint32>& presentSUIDs)
{
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    quint32 rSUID(0);

    do
    {
        rSUID = quint32(qrand());
    } while (presentSUIDs.contains(rSUID));

    return rSUID;
}

