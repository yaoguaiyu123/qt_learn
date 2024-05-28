#include "clientthread.h"
#include "client.h"
#include <QDebug>

ClientThread::ClientThread()
{
}

// 线程函数
void ClientThread::run()
{
    Client* client = new Client();
    if (!client->connectToServer("127.0.0.1", 1234)) {
        client->deleteLater(); // 释放内存
        return;
    }
    client->uploadFile("/root/test/from_2.mp4"); // 上传文件
}


ClientThread::~ClientThread()
{

}
