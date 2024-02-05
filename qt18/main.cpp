// Date:2024/2/5
// Author:妖怪鱼
// Introduction:TCP客户端编程(聊天室客户端)
#include "tcpclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpClient w;
    w.show();

    return a.exec();
}
