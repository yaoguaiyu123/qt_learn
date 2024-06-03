#include "fileclient.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QtEndian>
#include <QMutex>
#include <QMutexLocker>

namespace {
qint64 maxBlockSize = 512;   //一次读取的最大限制

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
{
    m_sendbuf = new uchar(8 * 4 * 1024);
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


/// 封装一个包进行发送,依次写入包的开头,包的大小，文件大小,文件名长度，文件名，文件数据长度，文件数据
void FileClient::uploadFile(const QString& filePath)
{
    qDebug() << "执行上传";
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
        QByteArray namebyteArray = newFileName.toUtf8();
        while (offset < totalSize) {
            // QThread::msleep(1);
            file.seek(offset);
            QByteArray dataBlock = file.read(maxBlockSize); // 读出文件数据
            qint32 size = sizeof(char) + sizeof(qint32) * 4 + namebyteArray.length() + dataBlock.length(); // 计算包的大小
            quint64 bytestowrite = 0;
            {
                //对sendBuf的写入做互斥
                QMutexLocker locker(&mutex);

                m_sendbuf[bytestowrite++] = beginC; // 开头
                qToBigEndian<qint32>(size, m_sendbuf + bytestowrite); // 包的大小
                bytestowrite += sizeof(qint32);
                qToBigEndian<qint32>(totalSize, m_sendbuf + bytestowrite); // 文件总大小
                bytestowrite += sizeof(qint32);
                qToBigEndian<qint32>(namebyteArray.length(), m_sendbuf + bytestowrite); // 名字长度
                bytestowrite += sizeof(qint32);
                for (int i = 0; i < namebyteArray.length(); ++i) {
                    m_sendbuf[bytestowrite++] = static_cast<uchar>(namebyteArray[i]); // 文件名
                }
                qToBigEndian<qint32>(dataBlock.length(), m_sendbuf + bytestowrite); // 数据长度
                bytestowrite += sizeof(qint32);
                for (int i = 0; i < dataBlock.length(); ++i) {
                    m_sendbuf[bytestowrite++] = static_cast<uchar>(dataBlock[i]); // 数据
                }
                // 异步调用
                QMetaObject::invokeMethod(this, "writeByteArray", Qt::QueuedConnection, Q_ARG(qint32, bytestowrite)); // 文件偏移
            }
            offset += dataBlock.size();
            // qDebug() << offset;
        }

        file.close();
    });
}




qint64 FileClient::writeByteArray(qint32 packageSize)
{
    qint32 pacHaveWritten = 0;
    qint32 oneTimeWrite;
    do {
        oneTimeWrite = socket.write(reinterpret_cast<const char*>
            (m_sendbuf + pacHaveWritten), packageSize - pacHaveWritten);
        socket.waitForBytesWritten();
        pacHaveWritten += oneTimeWrite;
    } while (pacHaveWritten < packageSize);
    return pacHaveWritten;
}



FileClient::~FileClient(){
    delete[] m_sendbuf;
}
