#include "steganography.h"
#include <QBuffer>
#include <QDebug>

QByteArray Steganography::embedMessage(const QByteArray& imageData, const QString& message) {
    QImage image;
    if (!image.loadFromData(imageData)) {
        qDebug() << "Failed to load image";
        return QByteArray();
    }
    image = image.convertToFormat(QImage::Format_ARGB32);
    QByteArray bytes = message.toUtf8();
    QVector<bool> bvec;
    for (char byte : bytes) {
        for (int j = 0; j < 8; j++) {
            bvec.push_back((byte & (1 << j)) != 0);
        }
    }
    bvec.push_back(false); // End marker
    if (image.height() * image.width() * 3 < bvec.size()) {
        qDebug() << "Image too small";
        return QByteArray();
    }
    int idx = 0;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            if (idx >= bvec.size()) goto done;
            QRgb pix = image.pixel(x, y);
            int blue = qBlue(pix) & 0xFE | (bvec[idx++] ? 1 : 0);
            image.setPixel(x, y, qRgba(qRed(pix), qGreen(pix), blue, qAlpha(pix)));
        }
    }
done:
    QByteArray outData;
    QBuffer buffer(&outData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return outData;
}

QString Steganography::extractMessage(const QByteArray& imageData) {
    QImage image;
    if (!image.loadFromData(imageData)) {
        qDebug() << "Failed to load image";
        return "";
    }
    image = image.convertToFormat(QImage::Format_ARGB32);
    QVector<bool> bvec;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            int blue = qBlue(image.pixel(x, y));
            bvec.push_back(blue & 1);
        }
    }
    QByteArray bytes;
    char temp = 0;
    for (int j = 0; j < bvec.size(); j++) {
        temp |= (bvec[j] ? (1 << (j % 8)) : 0);
        if (j % 8 == 7) {
            bytes.append(temp);
            if (temp == 0) break;
            temp = 0;
        }
    }
    return QString::fromUtf8(bytes);
}
