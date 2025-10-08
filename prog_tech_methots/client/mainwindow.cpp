#include "mainwindow.h"
#include "functionsforclient.h"
#include "singltoneforclient.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(const QString& login, QWidget *parent) : QMainWindow(parent), login(login) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    QPushButton *task1Btn = new QPushButton("Task1 DES", this);
    QPushButton *task2Btn = new QPushButton("Task2 SHA384", this);
    QPushButton *task3Btn = new QPushButton("Task3 Chord", this);
    QPushButton *task4Btn = new QPushButton("Task4 Stego", this);
    QPushButton *statBtn = new QPushButton("Stat", this);
    layout->addWidget(task1Btn);
    layout->addWidget(task2Btn);
    layout->addWidget(task3Btn);
    layout->addWidget(task4Btn);
    layout->addWidget(statBtn);
    setCentralWidget(central);

    connect(task1Btn, &QPushButton::clicked, this, &MainWindow::onTask1);
    connect(task2Btn, &QPushButton::clicked, this, &MainWindow::onTask2);
    connect(task3Btn, &QPushButton::clicked, this, &MainWindow::onTask3);
    connect(task4Btn, &QPushButton::clicked, this, &MainWindow::onTask4);
    connect(statBtn, &QPushButton::clicked, this, &MainWindow::onStat);

    connect(Singltoneforclient::getInstance(), &Singltoneforclient::receivedMsg, this, &MainWindow::handleResponse);
}

void MainWindow::onTask1() {
    QString text = "test"; // Input from user
    FunctionsForClient ffc;
    ffc.sendTask1(login, text);
}

void MainWindow::onTask2() {
    QString text = "test";
    FunctionsForClient ffc;
    ffc.sendTask2(login, text);
}

void MainWindow::onTask3() {
    double left = -200, right = 300, epsilon = 1e-6;
    int maxIter = 1000000;
    FunctionsForClient ffc;
    ffc.sendTask3(login, left, right, epsilon, maxIter);
}

void MainWindow::onTask4() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray image = file.readAll();
    QString message = "secret";
    FunctionsForClient ffc;
    ffc.sendTask4(login, image, message);
}

void MainWindow::onStat() {
    FunctionsForClient ffc;
    ffc.sendStat(login);
}

void MainWindow::handleResponse(const QString& msg) {
    qDebug() << "Response:" << msg;
    // Update GUI with response
}
