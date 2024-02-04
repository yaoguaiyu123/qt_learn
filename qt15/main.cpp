// Date:2024/2/3
// Author:妖怪鱼
// Introduction:UDP服务器编程
#include "udpserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UDPServer w;
    w.show();
    return a.exec();
}
