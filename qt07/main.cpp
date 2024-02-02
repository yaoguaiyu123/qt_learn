// Date:2024/2/2
// Author:妖怪鱼
// Introduction:蝴蝶飞行(GraphicsView学习)
#include "mainwindow.h"
#include "butterfly.h"
#include <QGraphicsScene>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();  //场景
    scene->setSceneRect(QRectF(-200, -200, 400, 400));
    //设置QGraphicsScene 对象的边界矩形。它定义了场景中可以包含图形项（如小部件、绘图元素等）的区域。
    butterfly* bfly = new butterfly();
    bfly->setPos(0, 0);     //设置一开始图元相对于场景的偏移量为(0,0)
    scene->addItem(bfly);  //将图元加入到场景
    QGraphicsView* view = new QGraphicsView();  //视图
    view->setScene(scene);
    view->resize(400, 400);
    view->show();
    return a.exec();
}
