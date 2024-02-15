#include "widget.h"
#include <QDebug>
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE"); // 连接一个sqlite数据库
    database.setDatabaseName("test01.db");
    if (!database.open()) {
        QMessageBox::critical(0, "错误", "数据库打开失败！", QMessageBox::Ok);
        exit(0);
    }
    QMessageBox::information(0, "正确", "数据库打开成功", QMessageBox::Ok);
    QSqlQuery queryexec;
    // 创建一个表emp
    queryexec.exec("create table emp(empid int primary key,empname varchar(20))");
    qDebug() << "打印可能存在的错误:" << queryexec.lastError().text(); // 如果已经存在emp表的话这边将会打印错误
    // 插入记录
    queryexec.exec("insert into emp values(101,'DaYuan')");
    queryexec.exec("insert into emp values(102,'English')");
    queryexec.exec("insert into emp values(103,'David')");
    queryexec.exec("insert into emp values(104,'Nihao')");
    queryexec.exec("insert into emp values(105,'Kate')");
    qDebug() << "打印可能存在的错误:" << queryexec.lastError().text();
    // 查询表
    queryexec.exec("select * from emp");
    qDebug() << "职工编号:   职工姓名:";
    while (queryexec.next()) {
        qDebug() << queryexec.value(0).toInt() << "   " << queryexec.value(1).toString();
    }

}

Widget::~Widget()
{
}

