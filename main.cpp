#include <QCoreApplication>
#include "Server.h"
#include "Database/DAO.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    Server server;
//    server.start();
    DAO::getInstance().initDB();
    return a.exec();
}
