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
    DAO();
    DAO(const DAO&) = delete;
    DAO operator=(const DAO&) = delete;
    void loadDB() const;
    void loadDBfilled() const;
    mutable QSqlDatabase _maindb;
    mutable bool _inited;
public:
    static const DAO& getInstance();
    ~DAO();
    void initDB() const;
    void addUser(const User&) const;
    void addBinding(const Binding&) const;
    void addMessage(const Message&) const;
    // TODO getUsers();
    // TODO getMessages();
    // TODO getBindings();
};

#endif
