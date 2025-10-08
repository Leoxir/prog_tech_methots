#ifndef FUNCTIONS FORCLIENT_H
#define FUNCTIONS FORCLIENT_H

#include <QString>

class FunctionsForClient {
public:
    void sendAuth(const QString& login, const QString& password);
    void sendReg(const QString& login, const QString& password, const QString& email);
    void sendTask1(const QString& login, const QString& text);
    void sendTask2(const QString& login, const QString& text);
    void sendTask3(const QString& login, double left, double right, double epsilon, int maxIter);
    void sendTask4(const QString& login, const QByteArray& image, const QString& message);
    void sendStat(const QString& login);
};

#endif // FUNCTIONS FORCLIENT_H
