#ifndef _CORE_
#define _CORE_
#include <QObject>
#include <QMap>

class QTcpServer;
class UserDescriptor;

class Core : public QObject
{
    Q_OBJECT
private:
    QTcpServer* _tcpServer;
    QMap<quint32, UserDescriptor*> _clients;
    Core(const Core&) = delete;
    Core& operator=(const Core&) = delete;
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

const quint32 generateUniqueSUID(const QList<quint32>&);

#endif
