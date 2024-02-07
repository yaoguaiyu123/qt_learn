#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"
TimeServer::TimeServer(QObject *parent):QTcpServer(parent)
{
    dlg =(Dialog *)parent;   //获得自己的父控件
}

void TimeServer::incomingConnection(qint64 socketDescriptor)
{
    //当接收到信号
    TimeThread *thread = new TimeThread(socketDescriptor,0);
    connect(thread,SIGNAL(finished()),dlg,SLOT(slotShow()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),Qt::DirectConnection);
    thread->start();
}
