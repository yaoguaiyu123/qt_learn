#include "fileclienthandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtGlobal>
#include <QDir>
#include <QTime>
#include <QElapsedTimer>
#include <QtConcurrent/QtConcurrentRun>
#include <QMutexLocker>
#include "parsefiledata.h"

FileClientHandler::FileClientHandler(qintptr socketDescriptor)
    : m_socket(new QTcpSocket),
    m_dir(new QDir("/root/test"))
{
    m_socket->setSocketDescriptor(socketDescriptor);
    _mutex = new QMutex();
    connect(m_socket, &QTcpSocket::readyRead, this, &FileClientHandler::onReadyRead);
    timer.start();
}

// 读取数据
void FileClientHandler::onReadyRead()
{
    QMutexLocker locker(_mutex);
    m_recvbuf.append(m_socket->readAll());
    // QtConcurrent::run([this]() {
    //     parseFileData();
    // });
}


// 处理文件包数据
void FileClientHandler::parseFileData()
{
    while (!m_recvbuf.isEmpty()) {
        QDataStream stream(&m_recvbuf, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_12);
        // qDebug() << m_recvbuf.size();
        if (m_recvbuf.size() < sizeof(char) + sizeof(qint32) * 2) {
            return;
        }
        char beginC;
        qint32 size = -1; // 当前包的长度
        qint32 totalSize = -1;
        stream >> beginC >> size >> totalSize;

        if (beginC != '#' || size == -1) {
            return;
        } else if (m_recvbuf.size() < size) {
            return;
        }
        QByteArray bytefilename;
        QByteArray fileData;
        stream >> bytefilename;
        stream >> fileData;

        QString filename = QString::fromLatin1(bytefilename);

        if (!m_filemap.contains(filename)) {
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
        fileinfo->file->write(fileData);
        fileinfo->haveWrite += fileData.size();
        if (timer.elapsed() >= 500) {
            timer.restart();
            qDebug() << "已经写入: " << fileinfo->haveWrite << " 还剩: " << -fileinfo->haveWrite + totalSize;
        }
        QMutexLocker locker(_mutex);
        m_recvbuf.remove(0, sizeof(char) + sizeof(qint32) + sizeof(qint32) + bytefilename.size() + fileData.size() + 2 * sizeof(qint32));

        if (fileinfo->haveWrite == totalSize) {
            qDebug() << tr("%1 文件上传成功").arg(filename);
            delete fileinfo->file;
            fileinfo->file = nullptr;
            m_filemap.remove(filename);
            delete fileinfo;
            fileinfo = nullptr;
        }
    }
}
