#ifndef CUTDIALOG_H
#define CUTDIALOG_H
//头像剪切窗口
//这个窗口没有设置成透明的，但是由于其副窗口透明，所以这个窗口也是透明的
#include <QWidget>
#include <QPoint>

class CutDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CutDialog(QWidget* parent = nullptr);

protected:
    //重写这两个函数实现窗口拖动效果
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
signals:
private:
    QPoint m_pt;
    QPoint m_startPt;
    bool m_mouseDown;
};

#endif // CUTDIALOG_H
