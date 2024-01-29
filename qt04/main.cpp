// Date:2024/1/29
// Author:妖怪鱼
// Introduction:可扩展对话框
#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
