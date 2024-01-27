#include "content.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Content::Content(QWidget* parent)
    : QFrame(parent)
{
    stack = new QStackedWidget(this); // 将堆栈窗口加入到主窗口
    stack->setFrameStyle(QFrame::Panel | QFrame ::Raised); // 设置堆栈窗口的显示风格
    baseInfo = new Baseinfo();
    contact = new Contact();
    detail = new Detail();
    stack->addWidget(baseInfo);
    stack->addWidget(contact);
    stack->addWidget(detail);
    button1 = new QPushButton("修改");
    button2 = new QPushButton("关闭");
    QHBoxLayout* btnLayout = new QHBoxLayout(); // 创建一个横向布局
    btnLayout->addStretch(1);
    btnLayout->addWidget(button1);
    btnLayout->addWidget(button2);
    QVBoxLayout* layoutR = new QVBoxLayout(this); // 创建一个纵向布局，并应用到主窗口
    layoutR->setContentsMargins(10, 10, 10, 10);
    layoutR->setSpacing(6);
    layoutR->addWidget(stack);
    layoutR->addLayout(btnLayout);
}

Content::~Content()
{
}

