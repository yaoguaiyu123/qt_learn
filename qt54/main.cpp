// Date:2024/5/26
// Author:妖怪鱼
// Introduction: 多线程文件传输服务端
#include "mainwindow.h"
#include "server.h"
#include <QApplication>
#include <QDebug>
#include <QNetworkInterface>
void printLocalIPs() {
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QNetworkInterface &networkInterface : QNetworkInterface::allInterfaces()) {
        for (const QNetworkAddressEntry &entry : networkInterface.addressEntries()) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && entry.ip() != localhost) {
                qDebug() << "我的IP地址: " << entry.ip().toString();
            }
        }
    }
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    printLocalIPs();
    Server server;
    if (!server.startServer(QHostAddress::Any, 1234)) {
        qDebug() << "Failed to start server";
    }
    return a.exec();
}


