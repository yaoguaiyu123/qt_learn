#include "parsefiledata.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QElapsedTimer>
#include <QMutexLocker>
#include "fileclienthandler.h"

ParseFileData::ParseFileData(QObject* parent)
    : _clientHandler(qobject_cast<FileClientHandler*>(parent)),
    QThread { nullptr }
{
}

void ParseFileData::run()
{
    while (true) {
        if (!_clientHandler->m_recvbuf.isEmpty()) {
            QDataStream stream(&_clientHandler->m_recvbuf, QIODevice::ReadOnly);
            stream.setVersion(QDataStream::Qt_6_5);
            if (_clientHandler->m_recvbuf.size() < sizeof(char) + sizeof(qint32) * 2) {
                return;
            }
            char beginC;
            qint32 size = -1; // 当前包的长度
            qint32 totalSize = -1;
            stream >> beginC >> size >> totalSize;
            if (beginC != '#' || size == -1) {
                return;
            } else if (_clientHandler->m_recvbuf.size() < size) {
                return;
            }
            QByteArray bytefilename;
            QByteArray fileData;
            stream >> bytefilename;
            stream >> fileData;
            if (stream.status() != QDataStream::Ok) {
                qDebug() << "流状态不对";
                return;
            }
            QString filename = QString::fromLatin1(bytefilename);

            if (!_clientHandler->m_filemap.contains(filename)) {
                if (!_clientHandler->m_dir->exists("serverFile")) {
                    _clientHandler->m_dir->mkdir("serverFile");
                }
                QFile* qfile = new QFile(_clientHandler->m_dir->path() + "/serverFile/" + filename);
                if (!qfile->open(QIODevice::WriteOnly)) {
                    qDebug() << "Failed to create file: " << filename;
                    return;
                }
                FileInfo* fileinfo = new FileInfo;
                fileinfo->file = qfile;
                fileinfo->haveWrite = 0;
                _clientHandler->m_filemap.insert(filename, fileinfo);
            }

            FileInfo* fileinfo = _clientHandler->m_filemap.value(filename);
            fileinfo->file->write(fileData);
            fileinfo->haveWrite += fileData.size();
            if (_clientHandler->timer.elapsed() >= 500) {
                _clientHandler->timer.restart();
                qDebug() << "已经写入: " << fileinfo->haveWrite << " 还剩: " << -fileinfo->haveWrite + totalSize;
            }
            {
                QMutexLocker locker(_clientHandler->_mutex);
                _clientHandler->m_recvbuf.remove(0, sizeof(char) + sizeof(qint32) + sizeof(qint32) + bytefilename.size() + fileData.size() + 2 * sizeof(qint32));
            }
            if (fileinfo->haveWrite == totalSize) {
                qDebug() << tr("%1 文件上传成功").arg(filename);
                _clientHandler->m_filemap.remove(filename);
                if (fileinfo != nullptr) {
                    if (fileinfo->file != nullptr) {
                        delete fileinfo->file;
                        fileinfo->file = nullptr;
                    }
                    delete fileinfo;
                    fileinfo = nullptr;
                }
            }
        }
    }
}
