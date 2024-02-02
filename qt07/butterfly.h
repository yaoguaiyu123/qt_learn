#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QObject>
#include <QGraphicsItem>   //图形项
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>


class butterfly : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit butterfly(QObject* parent = nullptr);
    void timerEvent(QTimerEvent*); // QTimerEvent类主要用于处理定时器事件
    QRectF boundingRect() const; // 为图元限定边界范围，所有继承自QGraphicsItem的类都必须实现此函数
signals:
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    // 这是QGraphicsItem类中一个用于绘制图形项的虚函数
    // const QStyleOptionGraphicsItem *option 参数提供了项的样式选项，包括状态信息（例如，项是否被选中）和视图相关信息（例如，视图的缩放级别）
private:
    bool up;
    QPixmap pix_up;
    QPixmap pix_down;
    qreal angle;   //qreal是一个浮点数类型
};

#endif // BUTTERFLY_H
