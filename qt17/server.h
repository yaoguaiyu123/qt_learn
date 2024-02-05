#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "tcpclientsocket.h"

class Server : public QTcpServer
{
    Q_OBJECT // 添加宏(Q_OBJECT)是为了实现信号与槽的通信
        public : Server(QObject* parent = 0, int port = 0);
    QList<TcpClientSocket*> tcpClientSocketList;
signals:
    void updateServer(QString, int);
public slots:
    void updateClients(QString, int);
    void slotDisconnected(int);
//    void slotnewConnetion();
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
