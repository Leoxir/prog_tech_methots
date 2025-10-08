#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QTcpServer {
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void readClient();
    void disconnected();
};

#endif // TCPSERVER_H
