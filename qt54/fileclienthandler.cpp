#include "fileclienthandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtGlobal>
#include <QDir>
#include <QTime>
#include <QElapsedTimer>
#include <QtEndian>

#ifndef MIN_PACKAGE_LENGTH
#define MIN_PACKAGE_LENGTH 15
#endif

FileClientHandler::FileClientHandler(QTcpSocket * socket)
    : m_socket(socket),
    m_dir(new QDir("/root/test"))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &FileClientHandler::onReadyRead);
    m_single_recvbuf = new uchar[16 * 1024];  // 单个包的接收缓存数组
    timer.start();
}

// 读取数据
void FileClientHandler::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    if (data.isEmpty()) {
        return;
    }
    m_recvbuf.append(reinterpret_cast<uchar*>(data.data()),data.size());
    parseFileData(); // 处理数据
}

// 拷贝数据到单包缓冲区
void FileClientHandler::copyDataFromRecvBuf(uchar* dest, qint32 numBytes) {
    if (numBytes > m_recvbuf.capacity) {
        qDebug() << "请求数据超过容量";
        return;
    }
    qint32 firstPartLength = qMin(numBytes, m_recvbuf.capacity - m_recvbuf.beginIndex);
    memcpy(dest, m_recvbuf.buffer + m_recvbuf.beginIndex, firstPartLength);

    if (numBytes > firstPartLength) {
        memcpy(dest + firstPartLength, m_recvbuf.buffer, numBytes - firstPartLength);
    }
    // m_recvbuf.beginIndex = (m_recvbuf.beginIndex + numBytes) % m_recvbuf.capacity;
}


// 处理文件包数据
void FileClientHandler::parseFileData()
{
    while (m_recvbuf.getAvailableSpace() > 0) {
        /// new逻辑
        if (m_recvbuf.capacity - m_recvbuf.getAvailableSpace() < MIN_PACKAGE_LENGTH) {
            return;
        }
        // 取出 1 + sizeof(qint32) 个字节放到 m_single_recvbuf
        copyDataFromRecvBuf(m_single_recvbuf, 1 + sizeof(qint32));

        qint32 bytesRead = 0;
        if (m_single_recvbuf[0] != '#') {
            qDebug() << "数据包开头错误 " << m_single_recvbuf[0];
            return;
        }
        ++bytesRead;
        quint32 packageSize = qFromBigEndian<qint32>(reinterpret_cast<const uchar*>(
            m_single_recvbuf + bytesRead)); // 包大小
        bytesRead += sizeof(qint32);
        if (m_recvbuf.capacity - m_recvbuf.getAvailableSpace() < packageSize) {
            return;
        }
        // 取出 size - (1 + sizeof(qint32)) 个字节添加到 m_single_recvbuf
        copyDataFromRecvBuf(m_single_recvbuf + 1 + sizeof(qint32), packageSize - (1 + sizeof(qint32)));

        quint32 totalSize = qFromBigEndian<qint32>(reinterpret_cast<const uchar*>(
            m_single_recvbuf + bytesRead)); // 文件总大小
        bytesRead += sizeof(qint32);
        quint32 fileNameLength = qFromBigEndian<qint32>(reinterpret_cast<const uchar*>(
            m_single_recvbuf + bytesRead)); // 文件名长度
        bytesRead += sizeof(qint32);
        QByteArray fileNameByte(reinterpret_cast<const char*>(m_single_recvbuf + bytesRead),
            fileNameLength);  // 文件名
        bytesRead += fileNameLength;
        quint32 dataLength = qFromBigEndian<qint32>(reinterpret_cast<const uchar*>(
            m_single_recvbuf + bytesRead)); // 数据长度
        bytesRead += sizeof(qint32);
        QByteArray data(reinterpret_cast<const char*>(m_single_recvbuf + bytesRead), dataLength); // 数据
        bytesRead += dataLength;
        m_recvbuf.beginIndex = (m_recvbuf.beginIndex + bytesRead) % m_recvbuf.capacity; // 更新beginIndex

        QString filename = QString::fromUtf8(fileNameByte);
        if (!m_filemap.contains(filename)) {
            // 首次要创建文件
            if (!m_dir->exists("serverFile")) {
                m_dir->mkdir("serverFile");
            }
            QFile* qfile = new QFile(m_dir->path() + "/serverFile/" + filename);
            if (!qfile->open(QIODevice::WriteOnly)) {
                qDebug() << "Failed to create file: " << filename;
                return;
            }
            FileInfo* fileinfo = new FileInfo;
            fileinfo->file = qfile;
            fileinfo->haveWrite = 0;
            m_filemap.insert(filename, fileinfo);
        }

        FileInfo* fileinfo = m_filemap.value(filename);
        fileinfo->file->write(data);
        fileinfo->haveWrite += data.size();
        if (timer.elapsed() >= 500) {
            timer.restart();
            qDebug() << "已经写入: " << fileinfo->haveWrite << " 还剩: " << -fileinfo->haveWrite + packageSize;
        }

        if (fileinfo->haveWrite == totalSize) {
            m_filemap.remove(filename);
            qDebug() << tr("%1 文件上传成功").arg(filename);
            if (fileinfo) {
                if (fileinfo->file) {
                    delete fileinfo->file;
                }
                delete fileinfo;
            }
        }
    }
}
