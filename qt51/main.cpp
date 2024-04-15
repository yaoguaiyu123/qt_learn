// Date:2024/4/15
// Author:妖怪鱼
// Introduction:qt事件处理机制demo
// 默认事件处理机制一般是accept,也就是说，不会再向父组件传递事件
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
