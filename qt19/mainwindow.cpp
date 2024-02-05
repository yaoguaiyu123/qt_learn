#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建一个QNetworkAccessManager对象实例，用来发送网络请求和接收应答
    manager = new QNetworkAccessManager(this);
    // manager的finished信号在网络应答结束时发送
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    // 发起网络请求
    manager->get(QNetworkRequest(QUrl("file:///run/media/root/study/%E7%BD%91%E9%A1%B5html%E7%B4%A0%E6%9D%90/homePage.html")));
}

//QTextBrowser类用于显示富文本内容(支持字体大小颜色变化，html,链接)
void MainWindow::replyFinished(QNetworkReply* reply)
{
    qDebug() << "正在读取内容";
    QString all = reply->readAll();
    qDebug() << all;
//    QString str = "hello world";
    ui->textBrowser->setText(all);  // 更新UI上的文本
    //删除reply对象
    reply->deleteLater();
}


MainWindow::~MainWindow()
{
    delete ui;
}

