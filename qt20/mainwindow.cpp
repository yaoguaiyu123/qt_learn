#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("鼠标事件");
    statusLabel = new QLabel("当前位置:");
    statusLabel->setFixedWidth(100);
    mousePosLabel = new QLabel("");
    mousePosLabel->setFixedWidth(100);
    //statusBar()返回QMainWindow的状态栏对象
    statusBar()->addPermanentWidget(statusLabel);   //在QMainWindow的状态栏中增加控件
    statusBar()->addPermanentWidget(mousePosLabel);
    this->setMouseTracking(true);
    resize(400, 200);
}

// 当鼠标按下时此函数被调用
void MainWindow::mousePressEvent(QMouseEvent* e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    if (e->button() == Qt::LeftButton) {
        statusBar()->showMessage("左键:" + str);
    } else if (e->button() == Qt::RightButton) {
        statusBar()->showMessage("右键:" + str);
    } else if (e->button() == Qt::MiddleButton) {
        statusBar()->showMessage("中键:" + str);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    mousePosLabel->setText("(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")");
}

void MainWindow::mouseReleaseEvent(QMouseEvent* e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    statusBar()->showMessage("鼠标释放在:" + str, 3000); // 3000表示显示时间为3000ms
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* e)
{
    qDebug() << "双击";
}

MainWindow::~MainWindow()
{
}

