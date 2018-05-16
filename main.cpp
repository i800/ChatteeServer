#include <QCoreApplication>
#include "Server.h"
#include "Database/DAO.h"
#include "Encryption/PassGenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    Server server;
//    server.start();
//    DAO::getInstance().initDB();
    const QPair<QString, QString> passDesc
            = PassGenerator::getInstance().getEncryptedPass("hedfdfllof");
    qDebug() << passDesc.first << " " << passDesc.second;
    qDebug() << PassGenerator::getInstance().checkPass(passDesc, "hedfdfllof");
    return a.exec();
}
