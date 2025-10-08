#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DataBase : public QObject {
    Q_OBJECT
private:
    static DataBase* instance;
    QSqlDatabase db;
    DataBase(QObject *parent = nullptr);
public:
    static DataBase* getInstance();
    bool connectDB();
    bool addUser(const QString& login, const QString& password, const QString& email);
    bool authUser(const QString& login, const QString& password);
    int getStat(const QString& login);
    void updateStat(const QString& login, int stat);
    void updateSockId(const QString& login, int sockId);
    int getSockId(const QString& login);
};

#endif // DATABASE_H
