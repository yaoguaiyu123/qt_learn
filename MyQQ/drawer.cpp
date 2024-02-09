#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget* parent, Qt::WindowFlags f)
    :QToolBox(parent, f)
{
    // 布局
    setWindowTitle("请选择你的账号");
    setWindowIcon(QPixmap(":/images/qq.png"));
    toolButton1 = new QToolButton();
    toolButton1->setText(tr("超级加菲猫"));
    toolButton1->setIcon(QPixmap(":/images/head01.png"));
    toolButton1->setIconSize(QPixmap(":/images/head01.png").size());
    toolButton1->setAutoRaise(true);
    toolButton1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton2 = new QToolButton();
    toolButton2->setText(tr("不许说胖"));
    toolButton2->setIcon(QPixmap(":/images/head02.png"));
    toolButton2->setIconSize(QPixmap(":/images/head02.png").size());
    toolButton2->setAutoRaise(true);
    toolButton2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton3 = new QToolButton();
    toolButton3->setText(tr("吃口甜辣酱"));
    toolButton3->setIcon(QPixmap(":/images/head03.png"));
    toolButton3->setIconSize(QPixmap(":/images/head03.png").size());
    toolButton3->setAutoRaise(true);
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton4 = new QToolButton();
    toolButton4->setText(tr("菜不透"));
    toolButton4->setIcon(QPixmap(":/images/head04.png"));
    toolButton4->setIconSize(QPixmap(":/images/head04.png").size());
    toolButton4->setAutoRaise(true);
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton5 = new QToolButton();
    toolButton5->setText(tr("你真真真厉害"));
    toolButton5->setIcon(QPixmap(":/images/head05.png"));
    toolButton5->setIconSize(QPixmap(":/images/head05.png").size());
    toolButton5->setAutoRaise(true);
    toolButton5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton6 = new QToolButton();
    toolButton6->setText(tr("灰老师"));
    toolButton6->setIcon(QPixmap(":/images/head06.png"));
    toolButton6->setIconSize(QPixmap(":/images/head06.png").size());
    toolButton6->setAutoRaise(true);
    toolButton6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton7 = new QToolButton();
    toolButton7->setText(tr("蛋挞小屁孩"));
    toolButton7->setIcon(QPixmap(":/images/head07.png"));
    toolButton7->setIconSize(QPixmap(":/images/head07.png").size());
    toolButton7->setAutoRaise(true);
    toolButton7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton8 = new QToolButton();
    toolButton8->setText(tr("陈锐凝"));
    toolButton8->setIcon(QPixmap(":/images/pig.png"));
    toolButton8->setIconSize(QPixmap(":/images/pig.png").size());
    toolButton8->setAutoRaise(true);
    toolButton8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton9 = new QToolButton();
    toolButton9->setText(tr("落水无横"));
    toolButton9->setIcon(QPixmap(":/images/head08.png"));
    toolButton9->setIconSize(QPixmap(":/images/head08.png").size());
    toolButton9->setAutoRaise(true);
    toolButton9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QGroupBox* groupBox = new QGroupBox(); // 创建一个QGroupBox实例，对应抽屉"群成员"
    QVBoxLayout* layout = new QVBoxLayout(groupBox);
    layout->setAlignment(Qt::AlignLeft);
    layout->addWidget(toolButton1);
    layout->addWidget(toolButton2);
    layout->addWidget(toolButton3);
    layout->addWidget(toolButton4);
    layout->addWidget(toolButton5);
    layout->addWidget(toolButton6);
    layout->addWidget(toolButton7);
    layout->addWidget(toolButton8);
    layout->addWidget(toolButton9);
    layout->addStretch();
    this->addItem((QWidget*)groupBox, tr("群成员"));
    resize(240, 640);
    // 连接槽函数

    connect(toolButton1, SIGNAL(clicked(bool)), this, SLOT(showChatWidget1()));
    connect(toolButton2, SIGNAL(clicked(bool)), this, SLOT(showChatWidget2()));
    connect(toolButton3, SIGNAL(clicked(bool)), this, SLOT(showChatWidget3()));
    connect(toolButton4, SIGNAL(clicked(bool)), this, SLOT(showChatWidget4()));
    connect(toolButton5, SIGNAL(clicked(bool)), this, SLOT(showChatWidget5()));
    connect(toolButton6, SIGNAL(clicked(bool)), this, SLOT(showChatWidget6()));
    connect(toolButton7, SIGNAL(clicked(bool)), this, SLOT(showChatWidget7()));
    connect(toolButton8, SIGNAL(clicked(bool)), this, SLOT(showChatWidget8()));
    connect(toolButton9, SIGNAL(clicked(bool)), this, SLOT(showChatWidget9()));
}

void Drawer::showChatWidget1()
{
    chatWidget1 = new Widget(0,toolButton1->text()); // 没有父控件
    chatWidget1->setWindowTitle(toolButton1->text());
    chatWidget1->setWindowIcon(toolButton1->icon());
    chatWidget1->show();
}

void Drawer::showChatWidget2()
{
    chatWidget2 = new Widget(0,toolButton2->text());
    chatWidget2->setWindowTitle(toolButton2->text());
    chatWidget2->setWindowIcon(toolButton2->icon());
    chatWidget2->show();
}


void Drawer::showChatWidget3()
{
    chatWidget3 = new Widget(0,toolButton3->text());
    chatWidget3->setWindowTitle(toolButton3->text());
    chatWidget3->setWindowIcon(toolButton3->icon());
    chatWidget3->show();
}


void Drawer::showChatWidget4()
{
    chatWidget4 = new Widget(0,toolButton4->text());
    chatWidget4->setWindowTitle(toolButton4->text());
    chatWidget4->setWindowIcon(toolButton4->icon());
    chatWidget4->show();
}


void Drawer::showChatWidget5()
{
    chatWidget5 = new Widget(0,toolButton5->text());
    chatWidget5->setWindowTitle(toolButton5->text());
    chatWidget5->setWindowIcon(toolButton5->icon());
    chatWidget5->show();
}


void Drawer::showChatWidget6()
{
    chatWidget6 = new Widget(0,toolButton6->text());
    chatWidget6->setWindowTitle(toolButton6->text());
    chatWidget6->setWindowIcon(toolButton6->icon());
    chatWidget6->show();
}


void Drawer::showChatWidget7()
{
    chatWidget7 = new Widget(0,toolButton7->text());
    chatWidget7->setWindowTitle(toolButton7->text());
    chatWidget7->setWindowIcon(toolButton7->icon());
    chatWidget7->show();
}


void Drawer::showChatWidget8()
{
    chatWidget8 = new Widget(0,toolButton8->text());
    chatWidget8->setWindowTitle(toolButton8->text());
    chatWidget8->setWindowIcon(toolButton8->icon());
    chatWidget8->show();
}


void Drawer::showChatWidget9()
{
    chatWidget9 = new Widget(0,toolButton9->text());
    chatWidget9->setWindowTitle(toolButton9->text());
    chatWidget9->setWindowIcon(toolButton9->icon());
    chatWidget9->show();
}

