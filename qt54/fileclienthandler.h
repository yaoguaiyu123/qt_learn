#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QDir>
#include <QElapsedTimer>

struct FileInfo {
    QFile* file;
    qint32 haveWrite;
};

// 可以循环使用的缓冲区
struct RecvBuf {
    uchar* buffer;
    qint32 beginIndex;
    qint32 endIndex;
    qint32 capacity;
    RecvBuf(int cap = 1024 * 1024 * 16)
        : capacity(cap)
        , beginIndex(0)
        , endIndex(0)
    {
        buffer = new uchar[capacity];
    }
    ~RecvBuf()
    {
        delete[] buffer;
    }
    // 可用空间
    qint32 getAvailableSpace(){
        if (endIndex >= beginIndex) {
            return capacity - (endIndex - beginIndex + 1);
        } else {
            return beginIndex - endIndex - 1;
        }
    }

    // 将数据放入缓冲区的函数
    void append(const uchar* data, qint32 len)
    {
        if (len <= 0) {
            return;
        }
        qint32 availableSpace = getAvailableSpace();  //可用空间
        if (len > availableSpace) {
            qDebug() << "警告:大缓冲区内存已满!!!";
            return;
        }
        if (endIndex + 1 + len <= capacity) {
            // 直接添加
            memcpy(buffer + endIndex + 1, data, len);
            endIndex += len;
        } else {
            // 需要回绕
            qint32 part1Len = capacity - (endIndex + 1);
            memcpy(buffer + endIndex + 1, data, part1Len);
            qint32 part2Len = len - part1Len;
            memcpy(buffer, data + part1Len, part2Len);
            endIndex = part2Len - 1;
        }
        if (endIndex >= capacity) {
            endIndex -= capacity;  // 保持endIndex在有效范围内
        }
    }
};


//传输文件的网络套接字

class FileClientHandler : public QObject
{
    Q_OBJECT
public:
    FileClientHandler(QTcpSocket* socket);
private slots:
    void onReadyRead();
    void parseFileData();  //解析数据的函数
    void copyDataFromRecvBuf(uchar* dest, qint32 numBytes);  //拷贝数据的函数
private:
    QTcpSocket* m_socket;
    bool is_success = false;
    bool is_begin = false;
    RecvBuf m_recvbuf;
    uchar* m_single_recvbuf;
    QMap<QString, FileInfo*> m_filemap;  //存储文件路径的map
    QDir * m_dir;
    QElapsedTimer timer;
};

#endif // CLIENTHANDLER_H
