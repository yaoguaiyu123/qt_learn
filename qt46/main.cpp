// Date:2024/3/28
// Author:妖怪鱼
// Introduction:qt多线程学习
#include "widget.h"
#include <QThread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
