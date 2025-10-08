#include <QApplication>
#include "authregform.h"
#include "mainwindow.h"
#include "singltoneforclient.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Singltoneforclient::getInstance()->connectToServer();
    AuthRegForm form;
    form.show();
    QObject::connect(&form, &AuthRegForm::authSuccess, [&](const QString& login) {
        MainWindow *mw = new MainWindow(login);
        mw->show();
    });
    return a.exec();
}
