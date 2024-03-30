#include "widget.h"
#include <QCamera>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QScrollBar>
#include <QHostAddress>
#include <QDateTime>
#include <QCompleter>
#include <QStringListModel>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //音频
    _ainput = new AudioInput();
    _ainputThread = new QThread();
    _ainput->moveToThread(_ainputThread);
    _ainputThread->start();

    QPushButton* button1 = new QPushButton(this);
    button1->setText("开始录音");
    QPushButton* button2 = new QPushButton(this);
    button2->setText("结束录音");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);

    connect(button1, &QPushButton::clicked, _ainput, &AudioInput::startCollect);
    connect(button2, &QPushButton::clicked, _ainput, &AudioInput::stopCollect);

    resize(200,150);
}

Widget::~Widget()
{
    ;
}
