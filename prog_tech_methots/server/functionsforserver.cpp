#include "functionsforserver.h"
#include "database.h"
#include "des.h"
#include "sha384.h"
#include "chordmethod.h"
#include "steganography.h"
#include <QDebug>
#include <QByteArray>
#include <QString> // Убедитесь, что QString включён

QString FunctionsForServer::processRequest(const QString& request) {
    QStringList parts = request.split("&");
    if (parts.isEmpty()) return "error";
    QString cmd = parts[0];

    if (cmd == "auth") {
        if (parts.size() != 3) return "error";
        QString login = parts[1];
        QString password = parts[2];
        if (DataBase::getInstance()->authUser(login, password)) {
            DataBase::getInstance()->updateSockId(login, 1); // Dummy sockid
            return "auth_ok";
        }
        return "auth_fail";
    } else if (cmd == "reg") {
        if (parts.size() != 4) return "error";
        QString login = parts[1];
        QString password = parts[2];
        QString email = parts[3];
        if (DataBase::getInstance()->addUser(login, password, email)) return "reg_ok";
        return "reg_fail";
    } else if (cmd == "task1") {
        if (parts.size() != 3) return "error";
        QString login = parts[1];
        QString text = parts[2];
        DES des;
        std::string result = des.encrypt(text.toStdString(), "0123456789ABCDEF"); // Шифрование
        return QString::fromStdString(result); // Явное преобразование в QString
    } else if (cmd == "task2") {
        if (parts.size() != 3) return "error";
        QString login = parts[1];
        QString text = parts[2];
        SHA384 sha;
        return sha.hash(text);
    } else if (cmd == "task3") {
        if (parts.size() != 6) return "error";
        QString login = parts[1];
        double left = parts[2].toDouble();
        double right = parts[3].toDouble();
        double epsilon = parts[4].toDouble();
        int maxIter = parts[5].toInt();
        ChordMethod chord;
        double root = chord.findRoot(left, right, epsilon, maxIter);
        return QString::number(root);
    } else if (cmd == "task4") {
        if (parts.size() != 4) return "error";
        QString login = parts[1];
        QByteArray imageData = QByteArray::fromBase64(parts[2].toUtf8());
        QString message = parts[3];
        Steganography stego;
        QByteArray newImage = stego.embedMessage(imageData, message);
        return newImage.toBase64();
    } else if (cmd == "stat") {
        if (parts.size() != 2) return "error";
        QString login = parts[1];
        return QString::number(DataBase::getInstance()->getStat(login));
    }
    return "error";
}
