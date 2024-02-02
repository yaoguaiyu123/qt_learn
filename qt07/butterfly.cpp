#include "butterfly.h"
#include <random>
#include <cmath>
#include <iostream>

butterfly::butterfly(QObject *parent)
    : QObject{parent}
{
    up = true;
    pix_up.load("../07/up.png");
    pix_down.load("../07/down.png");
    startTimer(100);   //启动定时器，时间间隔为100ms
}

// 返回图元限定区域范围(一个矩形)，此范围是以图元自身的坐标系为基础设定的
// QRectF构造函数的前两个参数是矩形的左上角的坐标，后两个参数是矩形的宽和高
QRectF butterfly::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-pix_up.width() / 2 - adjust, -pix_up.height() / 2 - adjust,
        pix_up.width() + adjust * 2, pix_up.height() + adjust * 2);
}

// 图元类的内部函数paint
void butterfly::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (up) {
        painter->drawPixmap(boundingRect().topLeft(), pix_up); // toLeft()返回矩形的左上角的坐标(QPointF对象)
        up = !up;
    } else {
        painter->drawPixmap(boundingRect().topLeft(), pix_down);
        up = !up;
    }
}

// 启动定时器之后每隔100ms调用该函数
void butterfly::timerEvent(QTimerEvent*)
{
    // scene()函数返回和当前图元相关联的场景对象的指针
    // pos()函数返回当前图元相对于父图元或者场景的坐标(0,0)的偏移量
    qreal edgex = scene()->sceneRect().right() + boundingRect().width() / 2; // 限定蝴蝶飞的右边界
    qreal edgeTop = scene()->sceneRect().top() - boundingRect().height() / 2; // 限定蝴蝶飞的上边界
    qreal edgeBottom = scene()->sceneRect().bottom() + boundingRect().height() / 2; // 限定蝴蝶飞的下边界
    if (pos().x() >= edgex) {
        setPos(scene()->sceneRect().left(), pos().y()); // 设置当前图元的坐标
    }
    if (pos().y() <= edgeTop) {
        setPos(pos().x(), scene()->sceneRect().bottom());
    }
    if (pos().y() >= edgeBottom) {
        setPos(pos().x(), scene()->sceneRect().top());
    }
    std::default_random_engine e;
    e.seed(time(0));
    angle += (e() % 10) / 20.0; // e()用于生一个随机数
    qreal dx = fabs(sin(angle * M_PI) * 10.0); // 由于dx是fabs得到的，所以蝴蝶不能向左移动
    qreal dy = (e() % 20) - 10.0;
    QPointF pf = mapToParent(dx, dy);
    std::cout << "普通: " << dx << "   " << dy << std::endl;
    std::cout << "转换: " << pf.x() << "   " << pf.y() << std::endl;
    //实际上这边pf.x() == dx + pos().x() ,pf.y() == dy + pos().y()
    setPos(mapToParent(dx, dy));
    //    setPos(dx, dy);
}








