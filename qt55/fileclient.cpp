#include "fileclient.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>
#include <QFileInfo>
#include <QRandomGenerator>

namespace {
qint64 maxBlockSize = 1024;   //一次读取的最大限制

QString generateRandomAlphanumeric(int length) {
    QString alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    QString randomString;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->generate() % alphanumeric.length();
        randomString += alphanumeric.at(index);
    }
    return randomString;
}

qint64 generateRandomTenDigitNumber() {
    // 10位数字的最小值和最大值
    const qint64 minValue = 1000000000;
    const qint64 maxValue = 9999999999;

    // 使用QRandomGenerator生成指定范围内的随机数
    qint64 randomNumber = QRandomGenerator::global()->bounded(minValue, maxValue + 1);
    return randomNumber;
}

}

FileClient::FileClient(QObject* parent)
    : QObject(parent)
    , toWrite(0)
    , haveWritten(0)
{
    connect(&socket, &QTcpSocket::bytesWritten, this, &FileClient::handleBytesWritten);
}

bool FileClient::connectToServer(const QString& host, quint16 port)
{
    socket.connectToHost(host, port);
    if (!socket.waitForConnected(3000)) {
        qDebug() << "超时，连接服务器失败";
        return false;
    } else {
        qDebug() << "Connected to server!";
        return true;
    }
}


void FileClient::handleBytesWritten(qint64 size)
{
    haveWritten += size;
    if (haveWritten == toWrite) {
        qDebug() << "确认已经写入完毕";
        deleteLater(); // 释放内存
    }
}


// 封装一个包进行发送,依次写入包的开头,包的大小，文件名，文件数据
void FileClient::uploadFile(const QString& filePath)
{
    QtConcurrent::run([this, filePath]() {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open file: " << filePath;
            return;
        }
        char beginC = '#';
        qint32 offset = 0;
        qint32 totalSize = file.size();
        QString filename = QFileInfo(filePath).fileName();
        QString newFileName = generateRandomAlphanumeric(7) + "_" + filename;
        QByteArray namebyte = newFileName.toLatin1();
        int times = 0;
        while (offset < totalSize) {
            ++times;
            if (times == 20) {
                times = 0;
                QThread::msleep(5);
            }
            file.seek(offset);
            QByteArray buffer;
            QDataStream stream(&buffer, QIODevice::WriteOnly);
            stream.setVersion(QDataStream::Qt_6_5);

            QByteArray dataBlock = file.read(maxBlockSize);
            qint32 size = sizeof(char) + sizeof(qint32) * 4 + namebyte.size() + dataBlock.size();

            stream << beginC;
            stream << size;   //当前包的长度
            stream << totalSize;
            stream << namebyte;
            stream << dataBlock;

            QMetaObject::invokeMethod(this, "writeByteArray", Qt::QueuedConnection,
                Q_ARG(QByteArray, buffer));

            offset += dataBlock.size();
            qDebug() << "Offset: " << offset << " 当前包大小: " << size;
        }

        file.close();
    });
}



qint64 FileClient::writeByteArray(const QByteArray& byteArray)
{
    return socket.write(byteArray);
}



FileClient::~FileClient(){
}
