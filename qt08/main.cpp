// Date:2024/2/2
// Author:妖怪鱼
// Introduction:简单文件目录浏览器(Qt模型/视图结构学习)
#include "widget.h"
#include <QApplication>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFileSystemModel model;
    model.setRootPath("/root");
    QTreeView view1;
    QListView view2;
    QTableView view3;
    view1.setModel(&model);
    view2.setModel(&model);
    view3.setModel(&model);
    view1.setSelectionMode(QAbstractItemView::MultiSelection);    //设置view1对象的选择模式为多选
    view2.setSelectionModel(view1.selectionModel());   //与view1使用相同的选择模型
    view3.setSelectionModel(view1.selectionModel());
    QObject::connect(&view1, SIGNAL(doubleClicked(QModelIndex)), &view2, SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&view1, SIGNAL(doubleClicked(QModelIndex)), &view3, SLOT(setRootIndex(QModelIndex)));
    QSplitter* splitter = new QSplitter();  //QSplitter的默认布局是水平布局
    splitter->addWidget(&view1);
    splitter->addWidget(&view2);
    splitter->addWidget(&view3);
    splitter->setWindowTitle("模型/视图");
    splitter->show();
    return a.exec();
}
