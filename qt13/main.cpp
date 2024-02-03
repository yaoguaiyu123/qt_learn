// Date:2024/2/3
// Author:妖怪鱼
// Introduction:监视文件和目录变化小案例
#include "watcher.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Watcher w;
    w.show();
    return a.exec();
}
