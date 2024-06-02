#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include <QDir>
#include <QElapsedTimer>
#include <QMutex>
struct FileInfo {
    QFile* file;
    qint32 haveWrite;
};
class ParseFileData;
//传输文件的网络套接字

class FileClientHandler : public QObject
{
    Q_OBJECT
    friend ParseFileData;
public:
    FileClientHandler(qintptr socketDescriptor);
private slots:
    void onReadyRead();
    void parseFileData();  //解析数据的函数
private:
    QTcpSocket* m_socket;
    bool is_success = false;
    bool is_begin = false;
    QByteArray m_recvbuf;
    QMap<QString, FileInfo*> m_filemap;  //存储文件路径的map
    QDir * m_dir;
    QElapsedTimer timer;
    QMutex* _mutex;
    ParseFileData* _parseFileData;
};

#endif // CLIENTHANDLER_H
