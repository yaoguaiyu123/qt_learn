// Date:2024/2/3
// Author:妖怪鱼
// Introduction:获取文件信息小案例
#include "fileinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileInfo w;
    w.show();

    return a.exec();
}
