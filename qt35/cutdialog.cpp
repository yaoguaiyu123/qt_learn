#include "cutdialog.h"
#include <QMouseEvent>
#include <QDebug>

CutDialog::CutDialog(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0,0,150,150);
    m_mouseDown = false;
}


void CutDialog::mousePressEvent(QMouseEvent* event)
{
//        if (event->buttons() & Qt::LeftButton) {
//            m_pt = event->globalPos()  - this->geometry().topLeft();
//        }

    m_startPt = event->pos();
    m_mouseDown = event->button() == Qt::LeftButton;
}

void CutDialog::mouseMoveEvent(QMouseEvent* event)
{
    //        if (event->buttons() & Qt::LeftButton) {
    //            QPoint newp = event->globalPos() - m_pt;
    //            this->move(newp); // move函数移动当前控件(坐标相对于父控件的左上角)
    //        }

    QPoint dragPoint = event->pos();
    if (m_mouseDown) {
        QPoint p = QPoint(pos().x() + dragPoint.x() - m_startPt.x(), pos().y() + dragPoint.y() - m_startPt.y());

        QPoint dragEnd = p;
        dragEnd.setX(dragEnd.x() + rect().width());
        dragEnd.setY(dragEnd.y() + rect().height());
        p.setX(p.x() < 0 ? 0 : p.x());
        p.setY(p.y() < 0 ? 0 : p.y());
        p.setX(dragEnd.x() > parentWidget()->width() ? parentWidget()->width() - rect().width() : p.x());
        p.setY(dragEnd.y() > parentWidget()->height() ? parentWidget()->height() - rect().height() : p.y());
        move(p);
    }
}


void CutDialog::mouseReleaseEvent(QMouseEvent* event){

}
