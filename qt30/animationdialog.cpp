#include "animationdialog.h"
#include <QHBoxLayout>

AnimationDialog::AnimationDialog()
{
    resize(325,400);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    m_asw = new AnimationStackWidget(this);
    m_page01 = new Page01(this);
    m_page02 = new Page02(this);
    m_asw->addWidget(m_page01);
    m_asw->addWidget(m_page02);
    QObject::connect(m_page01, &Page01::page01Clicked, this, &AnimationDialog::onPage01Clicked);
    QObject::connect(m_page02, &Page02::page02Clicked, this, &AnimationDialog::onPage02Clicked);
    layout->addWidget(m_asw);
    this->setLayout(layout);

}

// 实现翻转
void AnimationDialog::onPage01Clicked()
{
    m_asw->setStartVal(0);  //翻转的起始值
    m_asw->setEndVal(180);  //翻转的结束值
    m_asw->animation(1);
}

//实现翻转
void AnimationDialog::onPage02Clicked(){
    m_asw->setStartVal(0);  //翻转的起始值
    m_asw->setEndVal(-180);  //翻转的结束值
    m_asw->animation(0);
}
