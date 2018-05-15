#ifndef _LOGGER_
#define _LOGGER_
#include <QObject>

class QString;

class Logger : public QObject
{
private:
    QString _folder;
    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;
public:
    Logger(const QString& folder = "Reports");
    ~Logger();
    void writeError(const QString&);
    void writeLog(const QString&);
};

#endif
