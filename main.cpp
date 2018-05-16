#include <QCoreApplication>
#include "Server.h"
#include "Database/DAO.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    Server server;
//    server.start();
    DAO dao;
    dao.initDB();
    return a.exec();
}
