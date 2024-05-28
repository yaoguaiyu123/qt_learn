#include "clienthandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QRandomGenerator>
#include <QDateTime>
#include <QtGlobal>
#include <QDir>

QString ClientHandler::getRandomString(int nLen)
{
    srand(QDateTime::currentMSecsSinceEpoch());
    const char ch[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size = sizeof(ch);
    char* str = new char[nLen + 1];
    int num = 0;
    for (int nIndex = 0; nIndex < nLen; ++nIndex)
    {
        num = rand() % (size - 1);
        str[nIndex] = ch[num];
    }
    str[nLen] = '\0';
    QString res(str);
    return res;
}

ClientHandler::ClientHandler(qintptr descriptor)
    : socketDescriptor(descriptor)
{
}

void ClientHandler::run()
{
    QTcpSocket socket;
    if (!socket.setSocketDescriptor(socketDescriptor)) {
        return;
    }
    QDir dir("/root/test");
    if (!dir.exists("serverFile")) {
        dir.mkdir("serverFile");
    }
    QString filepath = QString("/root/test/serverFile/to%1.mp4").arg(getRandomString(8));
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    qint64 recvSize = 0, totalSize = 0;
    while (socket.waitForReadyRead()) {
        QByteArray byteArray = socket.readAll();
        recvSize += byteArray.size();
        if (byteArray.isEmpty()) {
            continue;
        }
        if (byteArray[0] == 'U' && !is_begin) {
            qDebug() << "----begin----";
            //读出开头和大小
            is_begin = true;
            byteArray.remove(0, 1); // 去除开头
            QDataStream stream(&byteArray, QIODevice::ReadOnly);
            stream >> totalSize;
            byteArray.remove(0, sizeof(qint64));  //去除qint64
            file.write(byteArray);
        } else {
            file.write(byteArray);
        }
    }
    if(recvSize < totalSize){
        QFile::remove(filepath);
        qDebug() << "文件接收不完整，已删除";
    } else {
        qDebug() << "文件接收成功";
    }
    file.close();
    qDebug() << "----end----";
}


