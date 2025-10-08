#include <QCoreApplication>
#include "tcpserver.h"
#include "database.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    DataBase::getInstance()->connectDB();
    TcpServer server;
    if (server.listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server started";
    } else {
        qDebug() << "Server failed to start";
    }
    return a.exec();
}
