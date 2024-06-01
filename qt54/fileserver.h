#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThreadPool>
// 文件服务器

class FileServer : public QTcpServer
{
    Q_OBJECT

public:
    FileServer(QObject *parent = nullptr);
    ~FileServer();
    bool startFileServer(const QHostAddress &address, quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
};

#endif // SERVER_H
