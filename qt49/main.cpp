// Date:2024/4/2
// Author:妖怪鱼
// Introduction:获取屏幕内容的小demo
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
