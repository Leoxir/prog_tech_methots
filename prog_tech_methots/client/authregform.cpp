#include "authregform.h"
#include "functionsforclient.h"
#include "singltoneforclient.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

AuthRegForm::AuthRegForm(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLineEdit *loginEdit = new QLineEdit(this);
    QLineEdit *passwordEdit = new QLineEdit(this);
    QLineEdit *emailEdit = new QLineEdit(this);
    QPushButton *authBtn = new QPushButton("Auth", this);
    QPushButton *regBtn = new QPushButton("Reg", this);
    layout->addWidget(new QLabel("Login:"));
    layout->addWidget(loginEdit);
    layout->addWidget(new QLabel("Password:"));
    layout->addWidget(passwordEdit);
    layout->addWidget(new QLabel("Email (for reg):"));
    layout->addWidget(emailEdit);
    layout->addWidget(authBtn);
    layout->addWidget(regBtn);

    connect(authBtn, &QPushButton::clicked, [=]() {
        FunctionsForClient ffc;
        ffc.sendAuth(loginEdit->text(), passwordEdit->text());
    });

    connect(regBtn, &QPushButton::clicked, [=]() {
        FunctionsForClient ffc;
        ffc.sendReg(loginEdit->text(), passwordEdit->text(), emailEdit->text());
    });

    connect(Singltoneforclient::getInstance(), &Singltoneforclient::receivedMsg, [=](const QString& msg) {
        if (msg == "auth_ok" || msg == "reg_ok") {
            emit authSuccess(loginEdit->text());
            close();
        } else {
            qDebug() << msg;
        }
    });
}

void AuthRegForm::onAuth() {
    // Handled in constructor
}

void AuthRegForm::onReg() {
    // Handled in constructor
}
