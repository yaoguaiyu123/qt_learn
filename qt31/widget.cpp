#include "widget.h"
#include "ui_widget.h"
#include "iplineedit.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QPushButton* btn = new QPushButton(this);
    btn->setText("获取ip");
    IPLineEdit* lineEdit = new IPLineEdit(this);
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked, this, [=]() {
        qDebug()<< lineEdit->text();
    });
}

Widget::~Widget()
{
    delete ui;
}

