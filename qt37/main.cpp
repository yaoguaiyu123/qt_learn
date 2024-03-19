// Date:2024/3/19
// Author:妖怪鱼
// Introduction:qt6视频播放
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
