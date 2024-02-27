// Date:2024/2/27
// Author:妖怪鱼
// Introduction:最小化托盘显示及操作
// 主要使用的类是QSystemTrayIcon
#include "systemtray.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SystemTray w;
    w.show();
    return a.exec();
}
