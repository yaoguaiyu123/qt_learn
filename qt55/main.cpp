// Date:2024/5/26
// Author:妖怪鱼
// Introduction: 多线程文件传输客户端
#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}

