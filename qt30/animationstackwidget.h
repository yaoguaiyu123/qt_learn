#ifndef ANIMATIONSTACKWIDGET_H
#define ANIMATIONSTACKWIDGET_H

#include <QStackedWidget>
//自定义的堆栈窗口

class AnimationStackWidget : public QStackedWidget
{
    Q_OBJECT
    //Qt提供的属性系统
    //该宏定义rotateVal属性，规定其getter和setter方法
    Q_PROPERTY(float rotateVal READ rotateVal WRITE setRotateVal)
public:
    AnimationStackWidget(QWidget* widget = 0);
    ~AnimationStackWidget();
    void animation(int pageIndex); // 实现动画效果
    void setRotateVal(float val)
    {
        // 设置旋转值
        m_rotateVal = val;
    }
    float rotateVal()
    {
        return m_rotateVal;
    }
    int startVal()
    {
        return m_startVal;
    }
    void setStartVal(int val)
    {
        m_startVal = val;
    }
    int endVal()
    {
        return m_endVal;
    }
    void setEndVal(int val)
    {
        m_endVal = val;
    }

private:
    float m_rotateVal; // 旋转值
    int m_startVal;
    int m_endVal;
    int m_pageIndex;
private slots:
    void onValueChanged();
    void onFinished();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ANIMATIONSTACKWIDGET_H
