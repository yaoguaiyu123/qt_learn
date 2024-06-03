#ifndef CLIENT_H
#define CLIENT_H

// 文件传输的套接字

#include <QTcpSocket>
#include <QObject>
#include <QFile>
#include <QMutex>

class FileClient : public QObject
{
    Q_OBJECT

public:
    FileClient(QObject *parent = nullptr);
    bool connectToServer(const QString &host, quint16 port);
    void uploadFile(const QString& filePath);
    ~FileClient();
public slots:
    qint64 writeByteArray(qint32 packageSize);
signals:
private:
    QTcpSocket socket;
    QFile file;
    // qint64 haveWritten;
    // qint64 toWrite;
    QMutex mutex;
    uchar* m_sendbuf;  //发送缓冲区， TODO 需要做互斥
};

#endif // CLIENT_H
