// Date:2024/2/7
// Author:妖怪鱼
// Introduction:多线程客户端
#include "timeclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeClient w;
    w.show();

    return a.exec();
}
