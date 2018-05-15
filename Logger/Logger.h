#ifndef _LOGGER_
#define _LOGGER_
#include <QObject>

class Logger : public QObject
{
private:
    QString _folder;
    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;
public:
    static const Logger& getInstance();
    Logger(const QString& folder = "Reports");
    ~Logger();
    void writeError(const QString&) const;
    void writeLog(const QString&) const;
};

#endif
