// Date:2024/2/5
// Author:妖怪鱼
// Introduction:键盘事件
#include "keyevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyEvent w;
    w.show();
    return a.exec();
}
