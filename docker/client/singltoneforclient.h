#ifndef SINGLTONEFORCLIENT_H
#define SINGLTONEFORCLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>  // Используем QtNetwork для явного подключения

class Singltoneforclient : public QObject {
    Q_OBJECT
private:
    static Singltoneforclient* instance;
    QTcpSocket* socket;
    Singltoneforclient(QObject *parent = nullptr);
public:
    static Singltoneforclient* getInstance();
    void connectToServer();
    void sendMsgToServer(const QString& msg);
signals:
    void receivedMsg(const QString& msg);
private slots:
    void slotServerRead();
};

#endif // SINGLTONEFORCLIENT_H
