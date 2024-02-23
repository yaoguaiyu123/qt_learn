#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTransform>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//paintEvent 函数是在窗口部件需要重绘时被调用的。
//例如，当窗口部件第一次显示出来时，或者当窗口部件被覆盖、最小化然后再恢复、或者当窗口部件的内容需要更新时，paintEvent 函数都会被系统自动调用。
void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    // 实现平移
    if (type == 1) {
        QTransform transform;
        transform.translate(20, 10);
        p.setTransform(transform);
    } else if (type == 2) {
        QTransform transform;
        transform.translate(width() / 2, 10);      //这里设置了旋转中心，也设置了图片左上角的点（改变图片位置）
        transform.rotate(45, Qt::YAxis);
        p.setTransform(transform);
    }
    QPixmap pix(":/05.png");
    p.drawPixmap(0, 0, 280, 360, pix);
}


//平移按钮被点击
void MainWindow::on_pushButton_clicked()
{
    type = 1;
    update();  //update函数能调用paintEvent函数
}

//旋转按钮被点击
void MainWindow::on_pushButton_2_clicked()
{
    type = 2;
    update();
}

