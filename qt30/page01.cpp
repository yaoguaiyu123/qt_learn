#include "page01.h"
#include "ui_page01.h"
#include <QTransform>
#include <QPainter>

Page01::Page01(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page01)
{
    ui->setupUi(this);
}

Page01::~Page01()
{
    delete ui;
}

void Page01::on_pushButton_clicked()
{
    // 翻转到页面2
    emit page01Clicked();
}

void Page01::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    QPixmap pix(":/06.png");
    p.drawPixmap(0, 0, 325, 450, pix);
}
