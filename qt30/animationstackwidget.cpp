#include "animationstackwidget.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QTransform>

AnimationStackWidget::AnimationStackWidget(QWidget* widget)
    :QStackedWidget(widget)
{

}

// 实现动画效果
void AnimationStackWidget::animation(int pageIndex)
{
    m_pageIndex = pageIndex;
    // 创建动画
    QPropertyAnimation* ani = new QPropertyAnimation(this, "rotateVal");
    // 设置动画的持续时间
    ani->setDuration(700);
    ani->setEasingCurve(QEasingCurve::Linear);
    // 设置动画起始值,结束值
    ani->setStartValue(m_startVal);
    ani->setEndValue(m_endVal);
    QObject::connect(ani, &QPropertyAnimation::valueChanged, this, &AnimationStackWidget::onValueChanged);
    QObject::connect(ani, &QPropertyAnimation::finished, this, &AnimationStackWidget::onFinished);
    currentWidget()->hide();

    ani->start();
}

AnimationStackWidget::~AnimationStackWidget()
{
    ;
}


void AnimationStackWidget::onValueChanged()
{
    repaint();
}

void AnimationStackWidget::onFinished()
{
    // 动画结束
    widget(m_pageIndex)->resize(325, 400);  //堆栈窗口的widget(int indedx)函数引用返回对应下标的子窗口
    widget(m_pageIndex)->show();

    setCurrentWidget(widget(m_pageIndex));
}


void AnimationStackWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    QTransform transform;
    if (m_rotateVal <= 90 && m_rotateVal >= 0 && m_pageIndex == 1) {
        transform.translate(width() / 2, 0);
        transform.rotate(m_rotateVal, Qt::YAxis);
        p.setTransform(transform);
        QPixmap pix(":/06.png");
        p.drawPixmap(-width() / 2, 0, 325, 450, pix);
    } else if (m_rotateVal >= 90 && m_rotateVal <= 180) {
        transform.translate(width() / 2, 0);
        transform.rotate(m_rotateVal + 180, Qt::YAxis);
        p.setTransform(transform);
        QPixmap pix(":/05.png");
        p.drawPixmap(-width() / 2, 0, 325, 450, pix);
    } else if (m_rotateVal <= 0 && m_rotateVal >= -90 && m_pageIndex == 0) {
        transform.translate(width() / 2, 0);
        transform.rotate(m_rotateVal, Qt::YAxis);
        p.setTransform(transform);
        QPixmap pix(":/05.png");
        p.drawPixmap(-width() / 2, 0, 325, 450, pix);
    }else if(m_rotateVal <= -90 && m_rotateVal >= -180){
        transform.translate(width() / 2, 0);
        transform.rotate(m_rotateVal+180, Qt::YAxis);
        p.setTransform(transform);
        QPixmap pix(":/06.png");
        p.drawPixmap(-width() / 2, 0, 325, 450, pix);
    }
}

