#include "widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 150);
    button1 = new QPushButton(this);
    button2 = new QPushButton(this);
    button1->setText("开始执行线程");
    button2->setText("停止执行线程");
    QGridLayout* mainlayout = new QGridLayout(this);
    mainlayout->addWidget(button1, 0, 0);
    mainlayout->addWidget(button2, 0, 1);
    thread1 = new MyThread_1(1, this);
    thread2 = new MyThread_1(2, this);
    thread3 = new MyThread_1(3, this);
    thread4 = new MyThread_1(4, this);
    connect(button1, &QPushButton::clicked, this, &Widget::on_button1_clicked);
    connect(button2, &QPushButton::clicked, this, &Widget::on_button2_clicked);
}

Widget::~Widget()
{
}


void Widget::on_button1_clicked()
{
    qDebug() << "开始执行线程";
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
}

void Widget::on_button2_clicked()
{
    qDebug() << "结束执行线程";
    thread1->terminate();
    thread1->wait();
    thread2->terminate();
    thread2->wait();
    thread3->terminate();
    thread3->wait();
    thread4->terminate();
    thread4->wait();

}
