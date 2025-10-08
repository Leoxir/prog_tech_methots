#include "database.h"
#include <QDebug>

DataBase* DataBase::instance = nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
}

DataBase* DataBase::getInstance() {
    if (!instance) {
        instance = new DataBase();
    }
    return instance;
}

bool DataBase::connectDB() {
    if (!db.open()) {
        qDebug() << "Cannot open database: " << db.lastError();
        return false;
    }
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY NOT NULL, login TEXT NOT NULL UNIQUE, password TEXT NOT NULL, email TEXT NOT NULL UNIQUE, stat INTEGER DEFAULT 0, sockid INTEGER NOT NULL)");
    return true;
}

bool DataBase::addUser(const QString& login, const QString& password, const QString& email) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password, email, sockid) VALUES (?, ?, ?, 0)");
    query.bindValue(0, login);
    query.bindValue(1, password);
    query.bindValue(2, email);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::authUser(const QString& login, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE login = ?");
    query.bindValue(0, login);
    query.exec();
    if (query.next()) {
        return query.value(0).toString() == password;
    }
    return false;
}

int DataBase::getStat(const QString& login) {
    QSqlQuery query;
    query.prepare("SELECT stat FROM users WHERE login = ?");
    query.bindValue(0, login);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

void DataBase::updateStat(const QString& login, int stat) {
    QSqlQuery query;
    query.prepare("UPDATE users SET stat = ? WHERE login = ?");
    query.bindValue(0, stat);
    query.bindValue(1, login);
    query.exec();
}

void DataBase::updateSockId(const QString& login, int sockId) {
    QSqlQuery query;
    query.prepare("UPDATE users SET sockid = ? WHERE login = ?");
    query.bindValue(0, sockId);
    query.bindValue(1, login);
    query.exec();
}

int DataBase::getSockId(const QString& login) {
    QSqlQuery query;
    query.prepare("SELECT sockid FROM users WHERE login = ?");
    query.bindValue(0, login);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}
