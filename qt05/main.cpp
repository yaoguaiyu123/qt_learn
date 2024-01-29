// Date:2024/1/29
// Author:妖怪鱼
// Introduction:程序启动动画
#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("../05/05.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();  //让程序在显示启动动画的同时也能响应鼠标等其他事件
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
