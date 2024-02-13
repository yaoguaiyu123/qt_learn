// Date:2024/2/8
// Author:妖怪鱼
// Introduction:Qt数据库项目
// 这个项目比较复杂，在这里作统一介绍
#include "mainwindow.h"
#include "connectdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectDialog dialog;
    if (dialog.exec() != QDialog::Accepted) {
        return -1;
    }
    QFile *carDetails = new QFile("attribs.xml");
    MainWindow window("factory", "cars", carDetails);
    window.show();
    return a.exec();
}
