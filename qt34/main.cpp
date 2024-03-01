// Date:2024/2/29
// Author:妖怪鱼
// Introduction:聊天窗口的模拟实现
#include <QApplication>
#include "widget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
