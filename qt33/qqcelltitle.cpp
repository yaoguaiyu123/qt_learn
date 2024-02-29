#include "qqcelltitle.h"
#include "ui_qqcelltitle.h"
#include <QDebug>
#include <QPainter>

QQCellTitle::QQCellTitle(QString groupName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQCellTitle)
{
    ui->setupUi(this);
    ui->label_2->setText(groupName);
    ui->label_3->setText(QString("[%1/%2]").arg(0).arg(0));
    this->setAttribute(Qt::WA_Hover, true); // 开启悬停事件
    this->installEventFilter(this); // 安装事件过滤器
    m_isOpen = false;
    m_cellIsHover = false;

}

QQCellTitle::~QQCellTitle()
{
    delete ui;
}


void QQCellTitle::setOnlineAndGroup(int onlineCount, int groupCount)
{
    ui->label_3->setText(QString("[%1/%2]").arg(onlineCount).arg(groupCount));
}

//事件过滤器返回true,表示已经拦截了事件，返回false表示不拦截事件
bool QQCellTitle::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this) {
        if (event->type() == QEvent::HoverEnter) { // 进入悬浮
            m_cellIsHover = true;
            repaint();
            return true;
        } else if (event->type() == QEvent::HoverLeave) { // 离开悬停
            m_cellIsHover = false;
            repaint();
            return true;
        } else if (event->type() == QEvent::MouseButtonPress) { // 鼠标点击
//            qDebug() << "点击";
            emit(QQCellTitle::sigCellStatusChange(m_isOpen));
            m_isOpen = !m_isOpen;
            if(m_isOpen){
                ui->label->setPixmap(QPixmap(":/images/向下箭头.png"));
            }else{
                ui->label->setPixmap(QPixmap(":/images/向右箭头.png"));
            }
        } else if (QEvent::Paint == event->type()) {
            //绘图事件不拦截
            return false;
        }
    }
    return false;
}


void QQCellTitle::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    if (m_cellIsHover) {
        p.setBrush(QColor(180, 180, 180));
    } else {
        p.setBrush(QColor(255, 255, 255));
    }
    p.drawRect(rect());

}
