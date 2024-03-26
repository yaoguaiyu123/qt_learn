// Date:2024/3/26
// Author:妖怪鱼
// Introduction:qt6获取摄像头内容并且放到屏幕上的demo
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
