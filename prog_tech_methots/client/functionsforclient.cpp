#include "functionsforclient.h"
#include "singltoneforclient.h"
#include <QByteArray>

void FunctionsForClient::sendAuth(const QString& login, const QString& password) {
    QString msg = "auth&" + login + "&" + password;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendReg(const QString& login, const QString& password, const QString& email) {
    QString msg = "reg&" + login + "&" + password + "&" + email;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendTask1(const QString& login, const QString& text) {
    QString msg = "task1&" + login + "&" + text;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendTask2(const QString& login, const QString& text) {
    QString msg = "task2&" + login + "&" + text;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendTask3(const QString& login, double left, double right, double epsilon, int maxIter) {
    QString msg = "task3&" + login + "&" + QString::number(left) + "&" + QString::number(right) + "&" + QString::number(epsilon) + "&" + QString::number(maxIter);
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendTask4(const QString& login, const QByteArray& image, const QString& message) {
    QString msg = "task4&" + login + "&" + image.toBase64() + "&" + message;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}

void FunctionsForClient::sendStat(const QString& login) {
    QString msg = "stat&" + login;
    Singltoneforclient::getInstance()->sendMsgToServer(msg);
}
