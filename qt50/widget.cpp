#include "widget.h"
#include <QDebug>
#include <QEvent>
#include <QCloseEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    lineEdit = new QLineEdit(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(lineEdit);
    lineEdit->installEventFilter(this);
    this->installEventFilter(this);
    resize(200, 200);
}

Widget::~Widget()
{
}

// 返回true表示事件被识别，否则返回false
// 对鼠标和键盘事件event()函数有着特殊的处理机制
bool Widget::event(QEvent* event)
{
    qDebug() << "event()函数收到事件: " << m_ans++;
    return QWidget::event(event); // 调用父类的event函数,这里的QWidget指定的是父类的作用域
}

// watched表示监听的对象
//  返回true表示处理了事件，不再将事件传递给监听的对象
//  返回false表示未处理该事件，继续将事件传递给监听的对象
bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this) {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            qDebug() << "eventFilter拦截键盘事件: " << m_ans_key++;
            return true;
        } else if (event->type() == QEvent::Close) {
            qDebug() << "eventFilter检测到关闭事件";
            return false;
        }
        return false;
    } else if (watched == lineEdit) {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            qDebug() << "eventFilter输入截停: " << m_ans_key++;
            return true;
        }
    }
    return false;
}

// 该函数在部件启用时被event函数调用
void Widget::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "mouseMoveEvent监听到鼠标移动事件: " << m_ans_mouse++;
}

// 该函数在部件启用时被event函数调用
void Widget::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "mouseMoveEvent监听到鼠标按下事件: " << m_ans_mouse++;
}

void Widget::closeEvent(QCloseEvent* event)
{
    // 阻止窗口关闭
    event->ignore();
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Your App",
        tr("你确定要退出吗?\n"),
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

