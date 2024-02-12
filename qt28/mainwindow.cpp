#include "mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(const QString &factoryTable,const QString &carTable,QFile *carDetails,QWidget *parent)
    : QMainWindow(parent)
{
    QGroupBox* factory = createFactoryGroupBox();
    QGroupBox* cars = createCarGroupBox();
    QGroupBox* details = createDetailsGroupBox();
    // 布局
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(factory, 0, 0);
    layout->addWidget(cars, 1, 0);
    layout->addWidget(details, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();
    resize(850, 400);
    setWindowTitle("主从视图");
}

QGroupBox* MainWindow::createFactoryGroupBox()
{
    factoryView = new QTableView();
    factoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止编辑单元格内容
    factoryView->setSortingEnabled(true);       //允许用户对表格内容进行排序
    factoryView->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置选中单元格时会选中整行数据
    factoryView->setSelectionMode(QAbstractItemView::SingleSelection);  //单选
    factoryView->setShowGrid(false);  //不显示网格线
    factoryView->setAlternatingRowColors(true);   //表格将显示为行颜色交替
    QGroupBox* box = new QGroupBox("汽车制造商");
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(factoryView, 0, 0);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createCarGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("汽车"));
    carView = new QTableView;
    carView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    carView->setSortingEnabled(true);
    carView->setSelectionBehavior(QAbstractItemView::SelectRows);
    carView->setSelectionMode(QAbstractItemView::SingleSelection);
    carView->setShowGrid(false);
    carView->verticalHeader()->hide();
    carView->setAlternatingRowColors(true);
//    carView->setModel(carModel);
//    connect(carView, SIGNAL(clicked(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
//    connect(carView, SIGNAL(activated(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(carView);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createDetailsGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("详细信息"));
    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);    //当文本宽度超过控件宽度，自动换行显示
    profileLabel->setAlignment(Qt::AlignBottom);  //设置 QLabel 对象的文本对齐方式为底部对齐
    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);
    attribList = new QListWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(profileLabel, 0, 0, 1, 2);
    layout->addWidget(titleLabel, 1, 0, 1, 2);
    layout->addWidget(attribList, 2, 0, 1, 2);
    layout->setRowStretch(2, 1);
    box->setLayout(layout);
    return box;
}

//创建操作菜单
void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction(tr("添加"), this);
    QAction *deleteAction = new QAction(tr("删除"), this);
    QAction *quitAction = new QAction(tr("退出"), this);
    addAction->setShortcut(tr("Ctrl+A"));
    deleteAction->setShortcut(tr("Ctrl+D"));
    quitAction->setShortcut(tr("Ctrl+Q"));
    QMenu *fileMenu = menuBar()->addMenu(tr("操作菜单"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

//    connect(addAction, SIGNAL(triggered(bool)), this, SLOT(addCar()));
//    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(delCar()));
//    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
}

