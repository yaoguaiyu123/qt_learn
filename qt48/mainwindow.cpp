#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QDebug>
#include <QLabel>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /// MenuBar
    QMenu* addMenu = ui->menubar->addMenu("Add");
    QMenu* updateMenu = ui->menubar->addMenu("Update");
    QMenu* aboutMenu = ui->menubar->addMenu("About");
    // 创建动作
    QAction* addAction = new QAction(tr("Add Item"), this);
    QAction* updateAction = new QAction(tr("Update Item"), this);
    QAction* aboutAction = new QAction(tr("About App"), this);
    QAction* addAction1 = new QAction(tr("Add Item1"), this);
    QAction* addAction2 = new QAction(tr("Add Item2"), this);
    QAction* addAction3 = new QAction(tr("Add Item3"), this);

    // 将动作添加到相应的菜单
    addMenu->addAction(addAction);
    addMenu->addAction(addAction1);
    addMenu->addAction(addAction2);
    addMenu->addAction(addAction3);
    updateMenu->addAction(updateAction);
    aboutMenu->addAction(aboutAction);

    // 连接动作信号到槽函数（示例槽函数需自行实现）
    connect(addAction, &QAction::triggered, this, &MainWindow::onAddItem);
    connect(updateAction, &QAction::triggered, this, &MainWindow::onUpdateItem);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAboutApp);

    /// ToolBar
    QToolBar* toolBar1 = addToolBar("File");
    toolBar1->addAction(addAction);
    toolBar1->addAction(addAction1);
    toolBar1->addAction(addAction2);
    toolBar1->addAction(addAction3);
    QToolBar* toolBar2 = addToolBar("Translate");
    toolBar2->addAction(updateAction);
    QToolBar* toolBar3 = addToolBar("Move");
    toolBar3->addAction(aboutAction);

    /// StatusBar(底部)
    QLabel* label1 = new QLabel("StatusBarLabel");
    QLabel* label2 = new QLabel("testLabel");
    QLabel* label3 = new QLabel("fileLabel");
    ui->statusbar->addWidget(label1);
    ui->statusbar->addWidget(label2);
    ui->statusbar->addWidget(label3);
//    ui->statusbar->showMessage("Show Message");

}

void MainWindow::onAddItem()
{
    qDebug() << "onAddItem";
}

void MainWindow::onUpdateItem() {
    qDebug() << "onUpdateItem";
}

void MainWindow::onAboutApp() {
    qDebug() << "onAboutApp";
}

MainWindow::~MainWindow()
{
    delete ui;
}

