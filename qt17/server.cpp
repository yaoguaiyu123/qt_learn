#include "server.h"
#include <QDebug>
#include <QNetworkProxyFactory>

Server::Server(QObject* parent, int port):QTcpServer(parent)
{
    //    QNetworkProxyFactory::setUseSystemConfiguration(false);
    listen(QHostAddress::Any, port); // listen在指定的端口对任意地址进行监听
//    connect(this, SIGNAL(newConnection()), this, SLOT(slotnewConnetion()));
    qDebug() << "服务端正在监听客户端的消息.....";
}

// 当出现一个新的连接请求的时候，就会触发该函数
// incomingConnection函数的作用是创建一个新的QTcpSocket对象，并为该连接分配一个套接字描述符（socket descriptor）
void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "服务端获取一个新的连接,正在创建套接字.....";
    TcpClientSocket* tcpClientSocket = new TcpClientSocket(this); // 创建一个套接字
    connect(tcpClientSocket, SIGNAL(updateClients(QString, int)), this, SLOT(updateClients(QString, int)));
    connect(tcpClientSocket, SIGNAL(disConnected(int)), this, SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocketList.append(tcpClientSocket);
}

//void Server::slotnewConnetion(){
//    qDebug() << "服务端获取一个新的连接,正在创建套接字.....";
//}


void Server::updateClients(QString msg, int length)
{
    emit updateServer(msg, length); // 发出信号通知服务端对话框更新相应的状态
    // 服务器将收到的信息发送给每个客户端
    for (int i = 0; i < tcpClientSocketList.length(); ++i) {
        QTcpSocket* item = tcpClientSocketList.at(i);
        if (item->write(msg.toUtf8(), length) != length) {
            continue;
        }
    }
}

void Server::slotDisconnected(int descriptor){
    for(int i =0;i<tcpClientSocketList.length();++i){
        QTcpSocket *item  = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor){
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
}
