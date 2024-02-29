#include "qqcell.h"

QQCell::QQCell(QString name,int offsetCellGroupY,QWidget *parent)
    : QWidget{parent}
{
    m_onlineCount = 0;
    m_groupCount = 0;
    m_groupIsOpen = false;
    m_offsetCellGroupY = offsetCellGroupY;
    m_cellTitle = new QQCellTitle(name, this);
    m_cellTitle->setGeometry(0, 0, QQ_CELL_TITLE_WIDTH, QQ_CELL_TITLE_HEIGHT);
    m_cellContent = new QWidget(this);
    m_cellContent->setGeometry(0,QQ_CELL_TITLE_HEIGHT,QQ_CELL_WIDTH,0);
    connect(m_cellTitle, &QQCellTitle::sigCellStatusChange, this, &QQCell::sltCellStatusChange);
    this->setGeometry(0,m_offsetCellGroupY,QQ_CELL_WIDTH,QQ_CELL_TITLE_HEIGHT);
}

void QQCell::sltCellStatusChange(bool isOpen)
{
    //展开还是关闭设置的是m_cellContent的高度和this的高度
    if (!isOpen) {
        // 如果没有展开就展开
        // 设置大小
        int newHeight = QQ_CELL_LINE_HEIGHT * m_cellLines.size();
        m_cellContent->setMinimumHeight(newHeight);
        m_cellContent->setMaximumHeight(newHeight);
        this->setMinimumHeight(newHeight + QQ_CELL_TITLE_HEIGHT);
        this->setMaximumHeight(newHeight + QQ_CELL_TITLE_HEIGHT);
        this->setGeometry(0, m_offsetCellGroupY, QQ_CELL_WIDTH, newHeight + QQ_CELL_TITLE_HEIGHT);
    } else {
        // 如果展开就关闭
        m_cellContent->setMinimumHeight(0);
        m_cellContent->setMaximumHeight(0);
        this->setMinimumHeight(QQ_CELL_TITLE_HEIGHT);
        this->setMaximumHeight(QQ_CELL_TITLE_HEIGHT);
        this->setGeometry(0, m_offsetCellGroupY, QQ_CELL_WIDTH, QQ_CELL_TITLE_HEIGHT);
    }
    emit(sigCellStatusChange(this));
}


void QQCell::addCellFriend(QString name, bool isOnline)
{
    QQCellLine* cellLine = new QQCellLine(name, isOnline, m_cellContent);
    m_cellLines.append(cellLine);
    // 计算偏移量

    int offsetCellLineY = (m_cellLines.size() - 1) * QQ_CELL_LINE_HEIGHT;

    cellLine->setGeometry(0,offsetCellLineY,QQ_CELL_LINE_WIDTH,QQ_CELL_LINE_HEIGHT);


}


//重新设置偏移量
void QQCell::resizeGeometry(int offsetY){
    this->setGeometry(0, offsetY, width(), height());
}






