// Date:2024/3/30
// Author:妖怪鱼
// Introduction:MainWindow菜单栏状态栏等的学习
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
