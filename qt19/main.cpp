// Date:2024/2/5
// Author:妖怪鱼
// Introduction:简单网页浏览器
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
