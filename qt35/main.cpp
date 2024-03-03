// Date:2024/3/2
// Author:妖怪鱼
// Introduction:裁剪头像功能的实现
#include "pictureedit.h"
#include "cutdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureEdit w;
    w.show();
//    CutDialog c;
//    c.show();
    return a.exec();
}
