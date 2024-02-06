// Date:2024/2/5
// Author:妖怪鱼
// Introduction:多线程简单案例
#include "threaddialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadDialog w;
    w.show();
    return a.exec();
}
