// Date:2024/1/29
// Author:妖怪鱼
// Introduction:文本编辑器(熟悉QMainWindow)
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
