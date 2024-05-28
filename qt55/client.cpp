#include "client.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>

namespace {
qint64 maxBlock = 204800;   //一次读取的最大限制
}

Client::Client(QObject* parent)
    : QObject(parent)
    , toWrite(0)
    , haveWritten(0)
{
    socket.setSocketOption(QTcpSocket::LowDelayOption, 1);
    // connect(&socket, &QTcpSocket::bytesWritten, this, &Client::handleBytesWritten);
}

bool Client::connectToServer(const QString& host, quint16 port)
{
    socket.connectToHost(host, port);
    if (!socket.waitForConnected(2000)) {
        qDebug() << "连接服务端失败";
        return false;
    } else {
        qDebug() << "Connected to server!";
        return true;
    }
}


void Client::handleBytesWritten(qint64 size)
{
    // haveWritten += size;
    // qDebug() << "已写入:" << haveWritten << "需要写入:" << toWrite;
    // if (haveWritten == toWrite) {
    //     qDebug() << "确认已经写入完毕";
    //     deleteLater(); // 释放内存
    // }
}

void Client::uploadFile(const QString& filePath)
{

    // QtConcurrent::run([this, filePath]() {
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly)) {
            socket.write("U");
            qint64 fileOffset = 0;
            qint64 fileSize = file.size(); // 文件大小
            QByteArray sizeBytes;
            QDataStream stream(&sizeBytes, QIODevice::ReadOnly);
            stream << fileSize;   //写入文件大小
            socket.write(sizeBytes);
            while (fileOffset < fileSize) {
                qDebug() << fileOffset << "   " << fileSize;
                file.seek(fileOffset);
                QByteArray byteArray = file.read(maxBlock);
                socket.write(byteArray);
                fileOffset += byteArray.size();
            }
            socket.write("Z");
        } else {
            qDebug() << "文件路径错误";
        }
        file.close();  //关闭文件
    // });
}


// void Client::downloadFile(const QString &fileName, const QString &savePath)
// {
//     QDataStream out(&socket);
//     out << 'D' << fileName;

//     file.setFileName(savePath);
//     if (!file.open(QIODevice::WriteOnly)) {
//         qDebug() << "Failed to open file for writing!";
//     }
// }

// void Client::onReadyRead()
// {
//     QDataStream in(&socket);
//     QByteArray fileData;
//     in >> fileData;
//     if (file.isOpen()) {
//         file.write(fileData);
//         file.close();
//         qDebug() << "File downloaded successfully!";
//     }
// }


Client::~Client(){
}
