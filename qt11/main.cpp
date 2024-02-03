// Date:2024/2/3
// Author:妖怪鱼
// Introduction:文件系统的浏览
#include "fileview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileView w;
    w.show();
    return a.exec();
}
