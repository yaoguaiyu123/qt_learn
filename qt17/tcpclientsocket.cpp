#include "tcpclientsocket.h"
#include <QDebug>

TcpClientSocket::TcpClientSocket(QObject *parent)
    : QTcpSocket{parent}
{
    //readyRead()信号在有数据到来时发出
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    //disconnected()信号在断开连接时发出
    connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    //connected()信号在成功连接时发出
    connect(this, SIGNAL(connected()), this, SLOT(slotConnected()));
}

void TcpClientSocket::dataReceived()
{
    while (bytesAvailable() > 0) {
        int length = bytesAvailable();
        char buf[1024];
        read(buf, length);
        QString msg = buf;
        emit updateClients(msg,length);   //发出updateClients信号
    }
}

void TcpClientSocket::slotDisconnected()
{
    emit disConnected(this->socketDescriptor()); // 发出自定义的disConnected信号
}

void TcpClientSocket::slotConnected()
{
    qDebug() << "服务端成功创建套接字:" << this->socketDescriptor();
}
