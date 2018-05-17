#include <QCoreApplication>
#include "Core/Core.h"
#include "Database/DAO.h"
#include "Encryption/PassGenerator.h"
#include "BusinessLayer/User.h"
#include "BusinessLayer/Binding.h"
#include "BusinessLayer/Message.h"
#include "Protocol/Packet.h"
#include "Protocol/Packets/UserRegPacket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Core core;
    core.start();
    DAO dao;
    return a.exec();
}
