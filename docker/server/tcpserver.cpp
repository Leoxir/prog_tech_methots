#include "tcpserver.h"
#include "functionsforserver.h"
#include <QDebug>

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent) {}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    connect(client, &QTcpSocket::readyRead, this, &TcpServer::readClient);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::disconnected);
    qDebug() << "New client from:" << client->peerAddress().toString();
}

void TcpServer::readClient() {
    QTcpSocket *client = (QTcpSocket*)sender();
    while (client->bytesAvailable() > 0) {
        QString request = client->readAll();
        FunctionsForServer ffs;
        QString response = ffs.processRequest(request);
        client->write(response.toUtf8());
    }
}

void TcpServer::disconnected() {
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();
    client->deleteLater();
}
