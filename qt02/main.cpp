// Date:2024/1/26
// Author:妖怪鱼
// Introduction:综合案例---修改用户信息
#include "content.h"

#include <QApplication>
#include <QFont>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("AR PL KaitiM GB", 12); // 设置整个程序采用的字体和字号
    a.setFont(font);
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, 0); // 新建一个水平分割窗口,水平切割，没有父对象
    mainSplitter->setOpaqueResize(true);  //设置分割窗口的调整方式为不透明调整。
    //当设置为不透明调整时，分割窗口在调整大小时会显示一个不透明的矩形，而不是默认的半透明矩形。
    QListWidget* list = new QListWidget(mainSplitter); // 创建一个列表
    list->insertItem(0, "基本信息");
    list->insertItem(1, "联系方式");
    list->insertItem(2, "详细资料");
    Content* content = new Content(mainSplitter); // 新建content并加入到mainSplitter
    QObject::connect(list, SIGNAL(currentRowChanged(int)), content->stack, SLOT(setCurrentIndex(int)));
    mainSplitter->setWindowTitle("修改用户资料");
    mainSplitter->setMinimumSize(mainSplitter->minimumSize());
    mainSplitter->setMaximumSize(mainSplitter->maximumSize());
    mainSplitter->show();
    return a.exec();
}
