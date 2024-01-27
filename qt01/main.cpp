// Date:2024/1/26
// Author:妖怪鱼
// Introduction:qt基础

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
