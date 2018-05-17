#ifndef _DAO_
#define _DAO_
#include <QObject>
#include <QtSql>
#include "Logger/Logger.h"

class User;
class Binding;
class Message;

class DAO : public QObject
{
    Q_OBJECT
private:
    DAO(const DAO&) = delete;
    DAO operator=(const DAO&) = delete;
    void loadDB() const;
    void loadDBfilled() const;
    mutable QSqlDatabase _maindb;
    mutable bool _inited;
public:
    DAO();
    ~DAO();
    void initDB() const;
    bool addUser(const User&) const;
    bool addBinding(const Binding&) const;
    bool addMessage(const Message&) const;
    User getUserByUsername(const QString&) const;
    // TODO getMessages();
    // TODO getBindings();
};

#endif
