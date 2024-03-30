// Date:2024/3/29
// Author:妖怪鱼
// Introduction:qt多线程的坑 Timers cannot be started from another thread
#include "widget.h"
#include <QNetworkInterface>
#include <QLineEdit>
#include <QApplication>

//超级奇怪的bug

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}
