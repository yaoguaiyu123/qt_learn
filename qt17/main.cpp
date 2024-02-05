// Date:2024/2/4
// Author:妖怪鱼
// Introduction:TCP服务器编程(聊天室的服务端)
#include "tcpserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer w;
    w.show();
    return a.exec();
}

