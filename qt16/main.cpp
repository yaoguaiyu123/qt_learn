// Date:2024/2/3
// Author:妖怪鱼
// Introduction:UDP客户端编程
#include "udpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UDPClient w;
    w.show();
    return a.exec();
}
