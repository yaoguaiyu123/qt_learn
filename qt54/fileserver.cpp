#include "fileserver.h"
#include "fileclienthandler.h"
#include <QDebug>
#include <QTcpSocket>

FileServer::FileServer(QObject* parent)
    : QTcpServer(parent)
{
    qDebug() << "文件服务器开始监听";
    listen(QHostAddress::Any, 8081);
}

FileServer::~FileServer()
{
    QThreadPool::globalInstance()->waitForDone();
}

bool FileServer::startFileServer(const QHostAddress& address, quint16 port)
{
    qDebug() << tr("服务端开始在%1端口监听").arg(port);
    return listen(address, port);
}

// 接收
void FileServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "接收到新的文件上传请求";
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    FileClientHandler* clientHandler = new FileClientHandler(socket);
    QThread* thread = new QThread;
    clientHandler->moveToThread(thread);
    thread->start();
}
