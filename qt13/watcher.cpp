#include "watcher.h"
#include "ui_watcher.h"
#include <QVBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QApplication>

Watcher::Watcher(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Watcher)
{
    ui->setupUi(this);
    QStringList args = qApp->arguments();
    QString path;
    if (args.count() > 1) {
        path = args[1];
    } else {
        path = QDir::currentPath();
    }
    pathLabel = new QLabel();
    pathLabel->setText("监视的目录:" + path);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(pathLabel);
    fsWatcher.addPath(path); //
    connect(&fsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanged(QString)));
}

void Watcher::directoryChanged(QString path)
{
    QMessageBox::information(NULL, "目录发生变化", path);
}

Watcher::~Watcher()
{
    delete ui;
}

