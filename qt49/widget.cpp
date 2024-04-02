#include "widget.h"
#include <QLabel>
#include <QScreen>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_label = new QLabel(this);

    // QCursor::pos()返回鼠标光标的全局坐标
    // QApplication::screenAt(const QPoint &p) 返回p所在的屏幕
    //    QScreen* screen = QApplication::screenAt(QCursor::pos());

    // QApplication::primaryScreen() 返回系统主显示器的屏幕对象
    m_screen = QApplication::primaryScreen();
    if (m_screen == nullptr) {
        qDebug() << "创建QScreen指针失败";
    }
    m_pixmap = m_screen->grabWindow(0); // 获取指定id的窗口的内容，如果是0则表示获取整个屏幕的内容
    if (m_pixmap.isNull()) {
        qDebug() << "获取屏幕内容失败";
    }
    qDebug() << "height:" << m_pixmap.height() << "width:" << m_pixmap.width();

    setMouseTracking(true);

    m_pushbutton1 = new QPushButton(this);
    m_pushbutton1->setText("截图");
    connect(m_pushbutton1, &QPushButton::clicked, this, &Widget::grapSreen);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_label);
    mainLayout->addWidget(m_pushbutton1);

    resize(1280, 800);
//    update();
//    repaint();   //立即调用
}

void Widget::paintEvent(QPaintEvent* event)
{

    qDebug() << "触发屏幕重绘";
    QPainter painter(this);
    QRect rect(m_label->x(), m_label->y(), m_label->width(), m_label->height());
    painter.drawPixmap(rect, m_pixmap);
}

void Widget::grapSreen(){

    //m_screen只需要创建一次就行了
    m_pixmap = m_screen->grabWindow(0);
    if (m_pixmap.isNull()) {
        qDebug() << "获取屏幕内容失败";
    }
    update();
}

Widget::~Widget()
{
}

