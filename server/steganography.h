#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <QImage>
#include <QString>
#include <QByteArray>

class Steganography {
public:
    QByteArray embedMessage(const QByteArray& imageData, const QString& message);
    QString extractMessage(const QByteArray& imageData);
};

#endif // STEGANOGRAPHY_H
