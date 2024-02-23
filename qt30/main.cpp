// Date:2024/2/22
// Author:妖怪鱼
// Introduction:Qt动画
//这里分为两个部分，其中MainWindow实现的是类似css的translate,rotate效果
//AnimationDialog,AnimationDialogWidget,Page01,Page02实现的是rotate和translation效果,即动画效果
#include "mainwindow.h"
#include "animationdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    AnimationDialog d;
    d.show();
    return a.exec();
}
