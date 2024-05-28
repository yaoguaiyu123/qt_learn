#include "client.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>

namespace {
qint64 maxBlock = 16000;   //一次读取的最大限制
}

Client::Client(QObject* parent)
    : QObject(parent)
    , toWrite(0)
    , haveWritten(0)
{
    connect(&socket, &QTcpSocket::bytesWritten, this, &Client::handleBytesWritten);
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
    haveWritten += size;
    // qDebug() << "已写入:" << haveWritten << "需要写入:" << toWrite;
    if (haveWritten == toWrite) {
        qDebug() << "确认已经写入完毕";
        deleteLater(); // 释放内存
    }
}

void Client::uploadFile(const QString& filePath)
{

    QtConcurrent::run([this, filePath]() {
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly)) {
            QByteArray uData = QByteArray("U");
            QMetaObject::invokeMethod(this, "writeByteArray", Qt::QueuedConnection,
                Q_ARG(QByteArray, uData));
            qint64 fileOffset = 0;
            qint64 fileSize = file.size(); // 文件大小
            toWrite = fileSize + 1 + sizeof(qint64);
            QByteArray sizeBytes;
            QDataStream stream(&sizeBytes, QIODevice::WriteOnly);
            stream << fileSize;   //写入文件大小
            QMetaObject::invokeMethod(this, "writeByteArray", Qt::QueuedConnection,
                Q_ARG(QByteArray, sizeBytes));
            while (fileOffset < fileSize) {
                // qDebug() << fileOffset << "   " << fileSize;
                file.seek(fileOffset);
                QByteArray byteArray = file.read(maxBlock);
                QMetaObject::invokeMethod(this, "writeByteArray",
                    Qt::QueuedConnection, Q_ARG(QByteArray, byteArray));
                fileOffset += byteArray.size();
            }
        } else {
            qDebug() << "文件路径错误";
        }
        file.close();
    });
}


qint64 Client::writeByteArray(const QByteArray& byteArray)
{
    return socket.write(byteArray);
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
