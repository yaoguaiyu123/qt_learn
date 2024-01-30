#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("简单记事本");
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
    // 创建动作，菜单，工具栏
    createActions();
    createMenus();
    createToolBars();
    if (img.load("../06/06.png")) {
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img.scaled(200, 200))); // 缩放图片为200x200大小之后加入到showWidget
    }
}


void MainWindow::createActions()
{
    openFileAction = new QAction(QIcon("../06/dakai.png"), "打开", this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip("打开一个文件");
    newFileAction = new QAction(QIcon("../06/dakai.png"), "新建", this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip("新建一个文件");
    exitAction = new QAction(QIcon("../06/dakai.png"), "退出", this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("退出程序");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close())); // 连接槽函数
    copyAction = new QAction(QIcon("../06/dakai.png"), "复制", this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip("复制文件");
    connect(copyAction, SIGNAL(triggered()), showWidget->text, SLOT(copy())); // 连接槽函数
    cutAction = new QAction(QIcon("../06/dakai.png"), "剪切", this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip("剪切文件");
    connect(cutAction, SIGNAL(triggered()), showWidget->text, SLOT(cut())); // 连接槽函数
    pasteAction = new QAction(QIcon("../06/dakai.png"), "粘贴", this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip("粘贴文件");
    connect(pasteAction, SIGNAL(triggered()), showWidget->text, SLOT(paste())); // 连接槽函数
    aboutAction = new QAction("关于", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(QApplication::aboutQt()));

    printTextAction = new QAction(QIcon("../06/dakai.png"), tr("打印文本"), this);
    printTextAction->setStatusTip(tr("打印一个文本"));
    printImageAction = new QAction(QIcon("../06/dakai.png"), tr("打印图像"), this);
    printImageAction->setStatusTip(tr("打印一个图像"));
    zoomInAction = new QAction(QIcon("../06/dakai.png"), tr("放大"), this);
    zoomInAction->setStatusTip(tr("放大图片"));
    zoomOutAction = new QAction(QIcon("../06/dakai.png"), tr("缩小"), this);
    zoomOutAction->setStatusTip(tr("缩小图片"));
    rotate90Action = new QAction(QIcon("../06/dakai.png"), tr("旋转90"), this);
    rotate90Action->setStatusTip(tr("旋转90度"));
    rotate180Action = new QAction(QIcon("../06/dakai.png"), tr("旋转180"), this);
    rotate180Action->setStatusTip(tr("旋转180度"));
    rotate270Action = new QAction(QIcon("../06/dakai.png"), tr("旋转270"), this);
    rotate270Action->setStatusTip(tr("旋转270度"));
    mirrorVAction = new QAction(QIcon("../06/dakai.png"), tr("垂直翻转"), this);
    mirrorVAction->setStatusTip(tr("垂直翻转一个图片"));
    mirrorHAction = new QAction(QIcon("../06/dakai.png"), tr("水平翻转"), this);
    mirrorHAction->setStatusTip(tr("水平翻转一个图片"));
    undoAction = new QAction(QIcon("../06/dakai.png"), tr("撤销"), this);
    connect(undoAction, SIGNAL(triggered()), showWidget->text, SLOT(undo())); // 连接槽函数
    redoAction = new QAction(QIcon("../06/dakai.png"), tr("重做"), this);
    connect(redoAction, SIGNAL(triggered()), showWidget->text, SLOT(redo())); // 连接槽函数
}

void MainWindow::createMenus()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu(tr("文件")); // menuBar()函数引用返回当前MainWindow菜单栏
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    // 缩放菜单
    zoomMenu = menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);
    // 旋转菜单
    rotateMenu = menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);
    // 镜像菜单
    mirrorMenu = menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorHAction);
    mirrorMenu->addAction(mirrorVAction);
}

void MainWindow::createToolBars()
{
    //工具条是一个可移动的窗口，可以设置停靠区域
    // 文件工具条
    filetool = addToolBar("File"); // addToolBar函数在当前MainWindow中添加一个工具条
    filetool->addAction(openFileAction);
    filetool->addAction(newFileAction);
    filetool->addAction(printTextAction);
    filetool->addAction(printImageAction);
    // 编辑工具条
    zoomtool = addToolBar("Edit");
    zoomtool->addAction(copyAction);
    zoomtool->addAction(cutAction);
    zoomtool->addAction(pasteAction);
    zoomtool->addSeparator();
    zoomtool->addAction(zoomInAction);
    zoomtool->addAction(zoomOutAction);
    // 旋转工具条
    rotatetool = addToolBar("Rotate");
    rotatetool->addAction(rotate90Action);
    rotatetool->addAction(rotate180Action);
    rotatetool->addAction(rotate270Action);
    // 撤销重做工具条
    dotool = addToolBar("Redo");
    dotool->addAction(undoAction);
    dotool->addAction(redoAction);
}

MainWindow::~MainWindow()
{
}

