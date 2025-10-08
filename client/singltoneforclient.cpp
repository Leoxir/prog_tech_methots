#include "singltoneforclient.h"
#include <QHostAddress>
#include <QDebug>

Singltoneforclient* Singltoneforclient::instance = nullptr;

Singltoneforclient::Singltoneforclient(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Singltoneforclient::slotServerRead);
}

Singltoneforclient* Singltoneforclient::getInstance() {
    if (!instance) {
        instance = new Singltoneforclient();
    }
    return instance;
}

void Singltoneforclient::connectToServer() {
    socket->connectToHost("127.0.0.1", 33333);
    if (socket->waitForConnected()) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Not connected";
    }
}

void Singltoneforclient::sendMsgToServer(const QString& msg) {
    socket->write(msg.toUtf8());
}

void Singltoneforclient::slotServerRead() {
    QString msg = socket->readAll();
    emit receivedMsg(msg);
}
