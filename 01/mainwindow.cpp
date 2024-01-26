#include "mainwindow.h"
#include <QGridLayout>
const double PI = 3.14;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resize(600,300);
    QWidget* centralWidget = new QWidget(this); // 创建一个中央部件
    setCentralWidget(centralWidget); // 将中央部件设置为 QMainWindow 的主要部件

    label1 = new QLabel("请输入圆的半径", centralWidget); // 将部件添加到 centralWidget 上
    lineEdit = new QLineEdit(centralWidget);
    button = new QPushButton("计算", centralWidget);
    label2 = new QLabel("圆的面积为:", centralWidget);
    QGridLayout* layout = new QGridLayout(centralWidget); // 使用 centralWidget 作为布局管理器的父对象

    layout->addWidget(label1, 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(label2, 1, 0);
    layout->addWidget(button, 1, 1);

    // 槽函数连接
    connect(button, SIGNAL(clicked(bool)), this, SLOT(showArea()));
}


MainWindow::~MainWindow()
{
}

void MainWindow::showArea()
{
    bool ok;
    QString tempStr;
    QString valueStr = lineEdit->text(); // 获取文本内容
    int valueInt = valueStr.toInt(&ok);
    double area = valueInt * valueInt * PI;
    label2->setText("圆的面积为:"+tempStr.setNum(area));  //这里setNum函数实现了将数字转字符串类型,如果是浮点数就默认保留2位小数
}




