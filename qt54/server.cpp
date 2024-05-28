#include "server.h"
#include "clienthandler.h"
#include <QDebug>
#include <QTcpSocket>

Server::Server(QObject* parent)
    : QTcpServer(parent)
{
}

Server::~Server()
{
    QThreadPool::globalInstance()->waitForDone();
}

bool Server::startServer(const QHostAddress& address, quint16 port)
{
    qDebug() << tr("服务端开始在%1端口监听").arg(port);
    return listen(address, port);
}

// 接收
void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "~~~~~~~~new connection~~~~~~~";
    // QThreadPool默认自动删除QRunnable，在执行完run方法之后
    ClientHandler *handler = new ClientHandler(socketDescriptor);
    QThreadPool::globalInstance()->start(handler);
}
