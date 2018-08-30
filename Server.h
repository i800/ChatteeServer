#ifndef SERVER_H
#define SERVER_H

#include <QtGlobal> //to include qintptr
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

class Server : public QObject
{
    Q_OBJECT
private:
    QTcpServer* _tcpServer;
    QList<QTcpSocket*> m_clients;
    //deleted methods
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
public:
    Server();
    ~Server();
    void start(unsigned short port = 45654);
private slots:
    //slot for server
    void onNewConnection();
    //slots for clients
    void processMessage();
    void onConnectionClosed();
};

#endif // SERVER_H
