// Date:2024/4/15
// Author:妖怪鱼
// Introduction:qt事件处理机制的学习
// 事件处理顺序:事件过滤器,焦点控件的event(),焦点控件的event handler,如果焦点控件忽略事件
// 就传递给父控件,如果事件accept,事件就处理完毕,不再传递给父控件
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
