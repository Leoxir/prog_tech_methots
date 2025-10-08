#include "sha384.h"
#include <QCryptographicHash>

QString SHA384::hash(const QString& text) {
    QByteArray ba = QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha384);
    return ba.toHex();
}
