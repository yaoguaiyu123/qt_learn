#include "page02.h"
#include "ui_page02.h"
#include <QTransform>
#include <QPainter>

Page02::Page02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page02)
{
    ui->setupUi(this);
}

Page02::~Page02()
{
    delete ui;
}

void Page02::on_pushButton_clicked()
{
  // 翻转到页面2
    emit page02Clicked();

}

void Page02::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    QPixmap pix(":/05.png");
    p.drawPixmap(0, 0, 325, 450, pix);
}
