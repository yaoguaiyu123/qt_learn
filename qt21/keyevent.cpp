#include "keyevent.h"
#include <QPainter>
#include <QDebug>

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("键盘事件");
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
    setMinimumSize(512, 256);
    setMaximumSize(512, 256);
    width = size().width();
    height = size().height();
    pix = new QPixmap(width, height);
    pix->fill(Qt::white);
    image.load("../21/image.png");
    startX = 100;
    startY = 100;
    step = 20;
    drawPix();
    resize(512, 256);
}

void KeyEvent::drawPix()
{
    pix->fill(Qt::white);
    QPainter* painter = new QPainter();
    QPen pen(Qt::DotLine);
    for (int i = step; i < width; i += step) {
        // 绘图坐标中x轴从左到右
        // y轴从上到下
        painter->begin(pix); // 指定pix为绘图设备
        painter->setPen(pen);
        painter->drawLine(QPoint(i, 0), QPoint(i, height)); // 绘制平行的竖线
        painter->end();
    }
    for (int j = step; j < height; j += step) {
        painter->begin(pix);
        painter->setPen(pen);
        painter->drawLine(QPoint(0, j), QPoint(width, j)); // 绘制平行的横线
        painter->end();
    }
    painter->begin(pix);
    painter->drawImage(QPoint(startX, startY), image);
    painter->end();
}

void KeyEvent::keyPressEvent(QKeyEvent* event)
{
    // event->modifiers()返回触发事件时按下的所有修饰键的状态,常见的修饰键包括Shift、Ctrl、Alt(这里判断是不是Ctrl键)
    if (event->modifiers() == Qt::ControlModifier) {
        qDebug() << "小步移动";
        if (event->key() == Qt::Key_Left) {
            startX = (startX - 1 < 0) ? startX : startX - 1;
        }
        if (event->key() == Qt::Key_Right) {
            startX = (startX + 1 + image.width() > width) ? startX : startX + 1;
        }
        if (event->key() == Qt::Key_Up) {
            startY = (startY - 1 < 0) ? startY : startY - 1;
        }
        if (event->key() == Qt::Key_Down) {
            startY = (startY + 1 + image.height() > height) ? startY : startY + 1;
        }
    } else {
        qDebug() << "大步移动";
        startX = startX - startX % step;
        startY = startY - startY % step;
        if (event->key() == Qt::Key_Left) {
            startX = (startX - step < 0) ? startX : startX - step;
        }
        if (event->key() == Qt::Key_Right) {
            startX = (startX + step + image.width() > width) ? startX : startX + step;
        }
        if (event->key() == Qt::Key_Up) {
            startY = (startY - step < 0) ? startY : startY - step;
        }
        if (event->key() == Qt::Key_Down) {
            startY = (startY + step + image.height() > height) ? startY : startY + step;
        }
        if (event->key() == Qt::Key_Home) {
            startX = 0;
            startY = 0;
        }
        if (event->key() == Qt::Key_End) {
            startX = width - image.width();
            startY = height - image.height();
        }
    }
    drawPix();
    update(); // 触发界面重画，将会调用paintEvent函数
}


void KeyEvent::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0, 0), *pix);
    painter.end();
}

KeyEvent::~KeyEvent()
{
}

