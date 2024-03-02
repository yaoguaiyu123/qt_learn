#include "linemessage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QScrollBar>

LineMessage::LineMessage(const LineMessageData &messageData,MessageUser msgUser,QWidget *parent)
    : QWidget{parent}
{
    // 布局
    //    this->setMaximumHeight(80);
    m_selfHeight = 40;
    QHBoxLayout* hlayout = new QHBoxLayout(this);
    QVBoxLayout* vlayout = new QVBoxLayout();
    QLabel* labelHead = new QLabel(this);
    QWidget* widgetTitle = new QWidget();
    QWidget* widgetMsg = new QWidget();
    widgetTitle->setMinimumWidth(300);
    widgetTitle->setMaximumHeight(15);
    widgetMsg->setMinimumWidth(300);
    QLabel* labelTitle = new QLabel(widgetTitle);
    QLabel* labelMsg = new QLabel(widgetMsg);
    labelTitle->setMinimumWidth(300);
    labelTitle->setMaximumHeight(15);
    QFontMetrics fontMet(labelMsg->font());
    int fontHeight = fontMet.height(); // 获取字体的高度
    int messageHeight = (fontHeight + 2) * (messageData.lineCount + 1);
    labelMsg->setMinimumHeight(messageHeight);
    widgetMsg->setMinimumWidth(messageHeight);
    labelMsg->setMinimumWidth(300);
    labelHead->setPixmap(QPixmap(messageData.headImg));
    labelHead->setAlignment(Qt::AlignTop);
//    qDebug() << "labelhead->size(width and height):" << labelHead->width() << labelHead->height();
    labelMsg->setText(messageData.message);
    if(msgUser == MessageUser::MessageUser_Self){
        labelMsg->setStyleSheet("background:#0099FF;color:white;border-radius:5px;");
        labelTitle->setAlignment(Qt::AlignRight); // 这里设置的是label中文字的对齐方式
        labelMsg->setAlignment(Qt::AlignRight | Qt::AlignCenter);
        labelTitle->setText(tr("%1 %2").arg(QString("2024/2/29 21:48:50")).arg("吴博渊"));
        vlayout->addWidget(widgetTitle);
        vlayout->addWidget(widgetMsg);
        hlayout->addLayout(vlayout);
        hlayout->addWidget(labelHead);
        // setAlignment设置的是某个控件或者视图内部的内容的对齐方式
        hlayout->setAlignment(Qt::AlignRight);
    }else if(msgUser == MessageUser::Message_Counterpart){
        labelMsg->setStyleSheet("background:#FFFFFF;color:#000000;border-radius:5px;");
        labelTitle->setAlignment(Qt::AlignLeft);
        labelMsg->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
        labelTitle->setText(tr("%1 %2").arg("奥特曼卡尔").arg("2024/2/29 21:50:20"));
        vlayout->addWidget(widgetTitle);
        vlayout->addWidget(widgetMsg);
        hlayout->addWidget(labelHead);
        hlayout->addLayout(vlayout);
        hlayout->setAlignment(Qt::AlignLeft);
    }
    setMinimumHeight(messageHeight + m_selfHeight);
    qDebug() << "this->height:" << height();
//    this->setStyleSheet("background:#aaaaaa");
}
