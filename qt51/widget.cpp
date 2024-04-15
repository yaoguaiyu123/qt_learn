#include "widget.h"
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>
#include "lineedit.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->installEventFilter(this);
    lineEdit = new LineEdit(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(lineEdit);
}

bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this) {
        if (event->type() == QEvent::KeyPress) {
            qDebug() << "键盘按下";
            return true;
        }
    }
    return false;
}

Widget::~Widget()
{
}

