// Date:2024/4/15
// Author:妖怪鱼
// Introduction:qt事件处理机制demo

// (1)
// 当我们自定义重写了子控件的事件处理handler方法，就不会再将事件传递给父控件，比如我在这里重写了LineEdit的
// keyPressEvent方法，事件不会传递给父控件
// 但是没有重写的方法对应的事件将会传递给父控件,比如LineEdit的keyReleaseEvent方法

// (2)
// 但是反过来，我在LineEdit中重写了keyReleaseEvent方法，没有重写keyPressEvent，两个事件都不会传递给父控件
// 猜测是处理了keyReleaseEvent之后qt连带判断keyPressEvent也被处理了

// (3)
// 无效事件，如MouseMove对于LineEdit就是无效事件，LineEdit会处理该事件，不会传递给父控件

// (4)
// 对于Qt库中的控件，由于都没有自定义重写事件handler方法,所以事件一般都会传递给父控件

#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
