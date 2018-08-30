#ifndef _PASS_GENERATOR_
#define _PASS_GENERATOR_
#include <QObject>

class PassGenerator : public QObject
{
    Q_OBJECT
private:
    PassGenerator();
    PassGenerator(const PassGenerator&) = delete;
    PassGenerator& operator=(const PassGenerator&) = delete;
    const QString getRandomQString() const;
public:
    static const PassGenerator& getInstance();
    ~PassGenerator();
    const QPair<QString, QString> getEncryptedPass(const QString& pass) const;
    bool checkPass(const QPair<QString, QString>& passDesc,
                   const QString& pass) const;
};

#endif
