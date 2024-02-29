// Date:2024/2/27
// Author:妖怪鱼
// Introduction:QQ好友组件的模拟实现
//这边仅仅实现了两个好友组的情况
//大致架构
/**
QQCell ----QQCellTitle
       |
       |                    |----QQCellLine
       ----QQCellContent----|----QQCellLine
                            |----QQCellLine
 **/


#include "widget.h"
#include "qqcell.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
