#include "widget.h"
#include "qqcell.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    int offsetCellGroupY;
    resize(300, 600);
    m_cell = new QQCell("我的好友", 0, this);
    m_cell->addCellFriend(QString("大头兵"), true);
    m_cell->addCellFriend(QString("国王"), false);
    m_cell->addCellFriend(QString("老头"), true);
    offsetCellGroupY = m_cell->height();
    m_cell1 = new QQCell("同学",offsetCellGroupY,this);
    m_cell1->addCellFriend(QString("黑衣人"), true);
    m_cell1->addCellFriend(QString("温州人"), false);

    connect(m_cell, &QQCell::sigCellStatusChange, this, &Widget::sltCellStatusChange);
    connect(m_cell1, &QQCell::sigCellStatusChange, this, &Widget::sltCellStatusChange);
}

void Widget::sltCellStatusChange(QWidget* cell)
{
    cell = static_cast<QQCell*>(cell);
    //偏移在这边设置
    int offsetCellY = m_cell->height();
    m_cell1->resizeGeometry(offsetCellY);
//    if (cell == m_cell) {
//        // 我的好友
//        int offsetCellY = m_cell->height();
//        m_cell1->resizeGeometry(offsetCellY);

//    }else if(cell == m_cell1){
//        //同学


//    }
}


Widget::~Widget()
{
}

