#include "mainwindow.h"
#include <QTextEdit>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("程序启动动画");
    QTextEdit* edit = new QTextEdit();
    edit->setText("程序启动动画");
    setCentralWidget(edit);
    resize(600, 450);
//    sleep(1000); // 这段时间播放程序启动动画
}

MainWindow::~MainWindow()
{
}

