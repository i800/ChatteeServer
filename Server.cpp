#include "Server.h"

using namespace std;

Server::Server():
    _tcpServer(new QTcpServer())
{
    qDebug("Server created");
}

Server::~Server()
{
    //do some stuff before closing sockets
    qDebug("Server deleted.");
    _tcpServer->close();
    delete _tcpServer;
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::start(unsigned short port)
{
    if(!_tcpServer->listen(QHostAddress::Any, port))
    {
        throw _tcpServer->serverError();
    }
    else
    {
        qDebug("Server started");
        connect(_tcpServer, &QTcpServer::newConnection,
                this, &Server::onNewConnection);
    }
}

void Server::onNewConnection()
{
    QTcpSocket* pSocket = _tcpServer->nextPendingConnection();
    connect(pSocket, &QTcpSocket::readyRead, this, &Server::processMessage);
    connect(pSocket, &QTcpSocket::disconnected, this, &Server::onConnectionClosed);

    m_clients << pSocket;
    qDebug("A client connected.");
}

void Server::processMessage()
{
    QTcpSocket* pSender = qobject_cast<QTcpSocket*>(sender());
    QByteArray message = pSender->readAll();
    for (QTcpSocket *pClient : qAsConst(m_clients))
    {
        //if (pClient != pSender) //don't echo message back to sender
        //{
            pClient->write(message);
            pClient->flush();
        //}
    }
}

void Server::onConnectionClosed()
{
    QTcpSocket* pClient = qobject_cast<QTcpSocket*>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
