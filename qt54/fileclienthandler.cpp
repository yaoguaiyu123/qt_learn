#include "fileclienthandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QtGlobal>
#include <QDir>

FileClientHandler::FileClientHandler(QTcpSocket * socket)
    : m_socket(socket),
    m_dir(new QDir("/root/test"))
{
    connect(m_socket, &QTcpSocket::readyRead, this, &FileClientHandler::onReadyRead);

}

// 读取数据
void FileClientHandler::onReadyRead()
{
    m_recvbuf.append(m_socket->readAll());
    // parseFileData(); // 处理数据
    QMetaObject::invokeMethod(this, "parseFileData", Qt::QueuedConnection);
}

// 处理文件包数据
void FileClientHandler::parseFileData()
{
    while (m_recvbuf.size() > 0) {
        if (m_recvbuf.size() == 0) {
            qDebug() << "bag empty!";
            return;
        }
        qDebug() << "当前数组的长度: " << m_recvbuf.length();
        QDataStream stream(&m_recvbuf, QIODevice::ReadOnly);
        char beginC;
        qint32 size; // 当前这一个包中文件数据的大小
        qint32 totalSize;
        QByteArray bytefilename;
        QByteArray fileData;
        if (m_recvbuf.length() < sizeof(beginC) + sizeof(size) + sizeof(totalSize)
                + bytefilename.size() + fileData.size() + sizeof(int) * 2) {
            qDebug() << "bag too short!";
            return; // 当前包长度不够，下次再读
        }
        stream >> beginC >> size >> totalSize >> bytefilename >> fileData;
        if (beginC != '#') {
            qDebug() << "包产生错误";
            return;
        }
        QString filename = QString::fromLatin1(bytefilename);
        FileInfo* fileinfo;
        if ((fileinfo = m_filemap.value(filename, nullptr)) == nullptr) {
            // 新的文件
            if (!m_dir->exists("serverFile")) {
                m_dir->mkdir("serverFile");
            }
            QFile* qfile = new QFile(m_dir->path() + "/serverFile/" + filename);
            if (!qfile->open(QIODevice::WriteOnly)) {
                qDebug() << "文件创建失败 " << bytefilename.size();
                return;
            }

            fileinfo = new FileInfo;
            *fileinfo = { qfile, 0 };
            m_filemap.insert(filename, fileinfo);
        }
        fileinfo->file->write(fileData);
        fileinfo->haveWrite += fileData.size();
        qDebug() << "已经写入:" << fileinfo->haveWrite << "  总共:" << totalSize;
        // 需要注意的是,客户端使用stream写入的的时候，会在QByteArray和QString的前面加上长度(int)
        m_recvbuf.remove(0, sizeof(beginC) + sizeof(size) + sizeof(totalSize) + bytefilename.size() + fileData.size() + sizeof(qint32) * 2);
        if (fileinfo->haveWrite == totalSize) {
            // 一个文件已经传输完毕
            qDebug() << tr("%1文件已经传输完毕").arg(filename);
            FileInfo* fileinfo = m_filemap.value(filename);
            m_filemap.remove(filename);
            delete fileinfo->file;
            delete fileinfo;
        }
    }
}

