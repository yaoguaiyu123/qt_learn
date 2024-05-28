#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include "client.h"
#include <QDebug>
#include <QThreadPool>
#include "clientthread.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::topWidget)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 上传文件
void MainWindow::on_pushButton_2_clicked()
{
    // ClientThread* clientThread = new ClientThread();
    // QThreadPool::globalInstance()->start(clientThread);

    Client* client = new Client();
    if (!client->connectToServer("127.0.0.1", 1234)) {
        client->deleteLater(); // 释放内存
        return;
    }
    client->uploadFile("/root/test/from_2.mp4"); // 上传文件
}

