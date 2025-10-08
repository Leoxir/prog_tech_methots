#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QWidget>

class AuthRegForm : public QWidget {
    Q_OBJECT
public:
    AuthRegForm(QWidget *parent = nullptr);
signals:
    void authSuccess(const QString& login);
private slots:
    void onAuth();
    void onReg();
};

#endif // AUTHREGFORM_H
