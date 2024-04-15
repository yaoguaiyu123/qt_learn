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
