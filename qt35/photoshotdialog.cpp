#include "photoshotdialog.h"
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

PhotoShotDialog::PhotoShotDialog(QWidget* parent)
    : QWidget(parent)
{
    m_cutDialog = new CutDialog(this);
    m_cutDialog->show();
    qDebug() << "切割窗口:" << m_cutDialog->x() << "   " << m_cutDialog->pos().y();
    //设置透明
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(0,0,parentWidget()->width(),parentWidget()->height());
}

PhotoShotDialog::~PhotoShotDialog()
{
    ;
}


void PhotoShotDialog::paintEvent(QPaintEvent* event)
{
    QPainterPath painterPath;
    QPainterPath p;
//    p.addRect(x(), y(), this->rect().width(), this->rect().height());
    p.addRect(rect()); // 大窗口(限制范围)
    painterPath.addRect(m_cutDialog->geometry()); // 小窗口(裁剪范围)
    QPainterPath drawPath = p.subtracted(painterPath); // 获得大窗口减去小窗口的范围
    QPainter painter(this);
    painter.setOpacity(0.5);   //设置透明度
    painter.fillPath(drawPath,QBrush(Qt::black));    //在drawPath的范围类进行绘图(绘制黑色背景)
}

QRect PhotoShotDialog::getCurrentCutRect()
{
    return m_cutDialog->geometry();
}



