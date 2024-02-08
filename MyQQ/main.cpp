// Date:2024/2/7
// Author:妖怪鱼
// Introduction:仿QQ(版本一，实现群聊功能)
#include "drawer.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Drawer d;
    d.show();
    return a.exec();
}
