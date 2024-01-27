#ifndef CONTENT_H
#define CONTENT_H
#include <QDialog>
#include <QFrame>
#include <QPushButton>
#include "contact.h"
#include "detail.h"
#include "baseinfo.h"
#include <QSplitter>
#include <QStackedWidget>

//这里是堆栈窗口

class Content : public QFrame
{
Q_OBJECT

public:
Content(QWidget* parent = nullptr);
~Content();
QStackedWidget* stack;
private:
QPushButton *button1, *button2;
Baseinfo* baseInfo;
Contact* contact;
Detail* detail;
};
#endif // CONTENT_H
