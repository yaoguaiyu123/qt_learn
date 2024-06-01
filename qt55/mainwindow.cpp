#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include "fileclient.h"
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
    FileClient* client = new FileClient();   //创建客户端
    if (!client->connectToServer("10.253.61.31", 8081)) {
        client->deleteLater(); // 释放内存
        return;
    }
    client->uploadFile("/root/test/from_2.mp4"); // 上传文件
}

