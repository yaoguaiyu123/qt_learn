#ifndef DRAWER_H
#define DRAWER_H
//这个类显示头像列表
//主要使用的控件是QToolBox,QGroupBox
#include <QToolBox>
#include <QToolButton>
#include "widget.h"

class Drawer : public QToolBox
{
    Q_OBJECT
public:
    Drawer(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private:
    // 9个按钮对应群里的9个成员
    QToolButton *toolButton1, *toolButton2, *toolButton3, *toolButton4,
        *toolButton5, *toolButton6, *toolButton7, *toolButton8, *toolButton9;
    //各个用户聊天窗口对象的指针
    Widget* chatWidget1;
    Widget* chatWidget2;
    Widget* chatWidget3;
    Widget* chatWidget4;
    Widget* chatWidget5;
    Widget* chatWidget6;
    Widget* chatWidget7;
    Widget* chatWidget8;
    Widget* chatWidget9;
private slots:
    //显示各个用户聊天窗口的函数
    void showChatWidget1();
    void showChatWidget2();
    void showChatWidget3();
    void showChatWidget4();
    void showChatWidget5();
    void showChatWidget6();
    void showChatWidget7();
    void showChatWidget8();
    void showChatWidget9();

};

#endif // DRAWER_H
