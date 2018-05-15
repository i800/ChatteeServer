#include "DAO.h"

DAO::DAO():
    _maindb(QSqlDatabase::addDatabase("QSQLITE"))
{
    initDB();

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

void DAO::initDB()
{
    if (!QFile("maindb.sqlite").exists())
    {
        loadDBfilled();
    }
    else
    {
        loadDB();
    }
}

void DAO::loadDB()
{
    _maindb.setDatabaseName("maindb.sqlite");

    if (!_maindb.open())
    {
        Logger::getInstance().writeError("Cannot open the database");
    }
}

void DAO::loadDBfilled()
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
                 `from` INTEGER NOT NULL, \
                 `when` INTEGER NOT NULL, \
                 FOREIGN KEY(`idb`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE, \
                 PRIMARY KEY(`ida`,`idb`), \
                 FOREIGN KEY(`ida`) REFERENCES `Users`(`id`) \
                 ON DELETE CASCADE )");

#ifndef NDEBUG
    qDebug() << "The data table created";
#endif
}

void DAO::executeSql(const QString& query)
{
    _maindb.exec(query);
}
