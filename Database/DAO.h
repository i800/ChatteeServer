#ifndef _DAO_
#define _DAO_
#include <QObject>
#include <QtSql>
#include "Logger/Logger.h"

class DAO : public QObject
{
    Q_OBJECT
private:
    DAO(const DAO&) = delete;
    DAO operator=(const DAO&) = delete;
    void loadDB();
    void loadDBfilled();
    QSqlDatabase _maindb;
    bool _inited;
public:
    DAO();
    ~DAO();
    void initDB();
    void executeSql(const QString&);
    // TODO getUsers();
    // TODO getMessages();
    // TODO getBindings();
};

#endif
