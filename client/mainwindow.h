#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(const QString& login, QWidget *parent = nullptr);
private:
    QString login;
private slots:
    void onTask1();
    void onTask2();
    void onTask3();
    void onTask4();
    void onStat();
    void handleResponse(const QString& msg);
};

#endif // MAINWINDOW_H
