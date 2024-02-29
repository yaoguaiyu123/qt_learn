#include "qqcellline.h"
#include "ui_qqcellline.h"

QQCellLine::QQCellLine(const QString& name, bool isOnline,QWidget* parent) :
    QWidget(parent),
    ui(new Ui::QQCellLine)
{
    ui->setupUi(this);
    ui->label_2->setText(name);
    ui->label_3->setText(tr("当前用户状态:%1").arg(isOnline ? "在线" : "离线"));
}

QQCellLine::~QQCellLine()
{
    delete ui;
}
