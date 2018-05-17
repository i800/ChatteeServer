#include "DAO.h"
#include "BusinessLayer/User.h"
#include "BusinessLayer/Binding.h"
#include "BusinessLayer/Message.h"

DAO::DAO():
    _maindb(QSqlDatabase::addDatabase("QSQLITE")),
    _inited(false)
{
#ifndef NDEBUG
    qDebug() << "DAO created";
#endif
}

DAO::~DAO()
{
#ifndef NDEBUG
    qDebug() << "DAO deleted";
#endif
}

void DAO::initDB() const
{
    if (!QFile("maindb.sqlite").exists())
    {
        loadDBfilled();
    }
    else
    {
        loadDB();
    }

    _inited = true;
}

void DAO::loadDB() const
{
    _maindb.setDatabaseName("maindb.sqlite");

    if (!_maindb.open())
    {
        Logger::getInstance().writeError("Cannot open the database");
    }
}

void DAO::loadDBfilled() const
{
    loadDB();

    _maindb.exec("CREATE TABLE `Users` \
                 ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
                 `username` TEXT NOT NULL UNIQUE, \
                 `bio` TEXT, `email` TEXT NOT NULL UNIQUE, \
                 `pass` TEXT NOT NULL, \
                 `hashkey` TEXT NOT NULL )");

    _maindb.exec("CREATE TABLE `Bindings` \
                 ( `ida` INTEGER NOT NULL, \
                 `idb` INTEGER NOT NULL, \
                 FOREIGN KEY(`idb`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE, \
                 PRIMARY KEY(`ida`,`idb`), \
                 FOREIGN KEY(`ida`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE )");

    _maindb.exec("CREATE TABLE `Messages` \
                 ( `ida` INTEGER NOT NULL, \
                 `idb` INTEGER NOT NULL, \
                 `text` TEXT NOT NULL, \
                 `v_from` INTEGER NOT NULL, \
                 `v_when` INTEGER NOT NULL, \
                 FOREIGN KEY(`idb`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE, \
                 PRIMARY KEY(`ida`,`idb`), \
                 FOREIGN KEY(`ida`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE )");

#ifndef NDEBUG
    qDebug() << "The data table created";
#endif
}

void DAO::addUser(const User& user) const
{
    _maindb.exec(QString("INSERT INTO Users (username, bio, email, pass, hashkey) \
                         VALUES ('%1', '%2', '%3', '%4', '%5')")
                         .arg(user.username(),
                              user.bio() == Q_NULLPTR ? "-" : user.bio(),
                              user.email(),
                              user.pass(),
                              user.hashkey()));
}

void DAO::addBinding(const Binding& binding) const
{
    _maindb.exec(QString("INSERT INTO Bindings (ida, idb) \
                         VALUES (%1, %2)")
                         .arg(QString::number(binding.ida()),
                              QString::number(binding.idb())));
}

void DAO::addMessage(const Message& message) const
{
    _maindb.exec(QString("INSERT INTO Messages (ida, idb, text, v_from, v_when) \
                         VALUES (%1, %2, '%3', %4, %5)")
                         .arg(QString::number(message.ida()),
                              QString::number(message.idb()),
                              message.text(),
                              QString::number(message.from()),
                              QString::number(message.when())));
}
