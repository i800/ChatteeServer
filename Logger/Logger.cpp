#include "Logger.h"
#include <QDebug>
#include <QString>
#include <QDir>
#include <QDateTime>

Logger::Logger(const QString& folder):
    _folder(folder)
{
    if (!QDir(folder).exists())
    {
        QDir().mkdir(folder);
        QDir().mkdir(folder + "/Errors");
        QDir().mkdir(folder + "/Logs");
    }

#ifndef NDEBUG
    qDebug() << "Logger created";
#endif
}

Logger::~Logger()
{
#ifndef NDEBUG
    qDebug() << "Logger deleted";
#endif
}

void Logger::writeError(const QString& err)
{
    QString currentDT = QDateTime::currentDateTime().toString().simplified();
    currentDT.replace(" ", "").replace(":", "-");
    QString path(_folder + "/Errors/err-" + currentDT + ".txt");
    QFile file(_folder + "/Errors/err-" + currentDT + ".txt");

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream(&file) << err;
    }

    file.close();
}

void Logger::writeLog(const QString& log)
{
    QString currentDT = QDateTime::currentDateTime().toString().simplified();
    currentDT.replace(" ", "").replace(":", "-");
    QFile file(_folder + "/Logs/log-" + currentDT + ".txt");

    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream(&file) << log;
    }

    file.close();
}
