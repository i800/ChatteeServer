#include "PassGenerator.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QTime>

PassGenerator::PassGenerator()
{
#ifndef NDEBUG
    qDebug() << "PassGenerator created";
#endif
}

PassGenerator::~PassGenerator()
{
#ifndef NDEBUG
    qDebug() << "PassGenerator deleted";
#endif
}

const PassGenerator& PassGenerator::getInstance()
{
    static const PassGenerator instance;
    return instance;
}

const QString PassGenerator::getRandomQString() const
{
    const QString domain("abcdefghijklmnopqrstuvwxyz");
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));

    QString randomQString;
    for(int i(0); i < 32; ++i)
    {
        QChar nextChar = domain.at(qrand() % domain.length());
        randomQString.append(nextChar);
    }

    return randomQString;
}

const QPair<QString, QString> PassGenerator
    ::getEncryptedPass(const QString& pass) const
{
    const QString& salt = getRandomQString();
    QString encryptedPass = QString(QCryptographicHash
      ::hash(QByteArray::fromHex(pass.toUtf8()),
             QCryptographicHash::Sha512).toHex());
    QString encryptedSalt = QString(QCryptographicHash
      ::hash(QByteArray::fromHex(salt.toUtf8()),
             QCryptographicHash::Sha512).toHex());
    QString completedPass = QString(QCryptographicHash
      ::hash(QByteArray::fromHex((encryptedPass + encryptedSalt).toUtf8()),
             QCryptographicHash::Sha512).toHex());
    return QPair<QString, QString>(completedPass, salt);
}

bool PassGenerator::checkPass(const QPair<QString, QString>& passDesc,
                              const QString& pass) const
{
    QString encryptedPass = QString(QCryptographicHash
      ::hash(QByteArray::fromHex(pass.toUtf8()),
             QCryptographicHash::Sha512).toHex());
    QString encryptedSalt = QString(QCryptographicHash
      ::hash(QByteArray::fromHex(passDesc.second.toUtf8()),
             QCryptographicHash::Sha512).toHex());
    QString completedPass = QString(QCryptographicHash
      ::hash(QByteArray::fromHex((encryptedPass + encryptedSalt).toUtf8()),
             QCryptographicHash::Sha512).toHex());
    return completedPass == passDesc.first;
}
