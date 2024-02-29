#ifndef QQCELL_H
#define QQCELL_H

#include <QWidget>
#include "qqcelltitle.h"
#include <QList>
#include <QList>
#include "qqcellline.h"
#define QQ_CELL_WIDTH 300
#define QQ_CELL_TITLE_WIDTH 300
#define QQ_CELL_TITLE_HEIGHT 30
#define QQ_CELL_LINE_WIDTH 300
#define QQ_CELL_LINE_HEIGHT 50


class QQCell : public QWidget
{
    Q_OBJECT
public:
    explicit QQCell(QString name,int offsetCellGroupY = 0,QWidget* parent = nullptr);
    void addCellFriend(QString name,bool isOnline = true);   //添加好友函数
    void resizeGeometry(int offsetY = 0);  //设置偏移量
signals:
    void sigCellStatusChange(QWidget *);
private:
    int m_onlineCount;
    int m_groupCount;
    bool m_groupIsOpen; // 好友组是否展开
    QQCellTitle* m_cellTitle;
    QWidget* m_cellContent;
    QList<QQCellLine*> m_cellLines; // 好友组中的好友个数
    int m_offsetCellGroupY;  //整个好友组的偏移量

private slots:
    void sltCellStatusChange(bool);
};

#endif // QQCELL_H
