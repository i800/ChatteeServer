#include <QCoreApplication>
#include "Server.h"
#include "Database/DAO.h"
#include "Encryption/PassGenerator.h"
#include "BusinessLayer/User.h"
#include "BusinessLayer/Binding.h"
#include "BusinessLayer/Message.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    Server server;
//    server.start();
    DAO::getInstance().initDB();
    Message m(2, 3, "hello, bro ;)", 2, QDateTime::currentDateTime().toTime_t());
    DAO::getInstance().addMessage(m);
    return a.exec();
}
