// Date:2024/2/6
// Author:妖怪鱼
// Introduction:多线程服务端
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
