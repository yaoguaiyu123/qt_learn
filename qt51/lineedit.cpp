#include "lineedit.h"
#include <QDebug>
#include <QKeyEvent>

LineEdit::LineEdit(QWidget * parent)
    :QLineEdit(parent)
{

}

void LineEdit::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "LineEdit的keyPressEvent: " << m_count_key++;
}

// void LineEdit::keyReleaseEvent(QKeyEvent* event)
//{
//     qDebug() << "LineEdit的keyReleaseEvent: " << m_count_key++;
// }

bool LineEdit::event(QEvent* event)
{
    if (event->type() == QEvent::MouseMove) {
        qDebug() << "鼠标在LineEdit上移动";
    }
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
//        qDebug() << "LineEdit::event()";
    }
    return QWidget::event(event);
}
