#ifndef _CORE_
#define _CORE_

#include <QtGlobal> //to include qintptr
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

class Core : public QObject
{
    Q_OBJECT
private:
    QTcpServer* _tcpServer;
    QList<QTcpSocket*> m_clients;
    //deleted methods
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
public:
    Core();
    ~Core();
    void start(unsigned short port = 45654);
private slots:
    //slot for Core
    void onNewConnection();
    //slots for clients
    void processMessage();
    void onConnectionClosed();
};

#endif
