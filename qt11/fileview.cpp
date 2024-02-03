#include "fileview.h"

FileView::FileView(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("file view");
    fileLineEdit = new QLineEdit("/");
    fileListWidget = new QListWidget();
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(fileLineEdit);
    mainLayout->addWidget(fileListWidget);
//    connect(fileLineEdit, SIGNAL(returnPressed()), this, SLOT(slotShow(QDir)));

    connect(fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotDirShow(QListWidgetItem*)));
    QString root = "/";
    QDir rootDir(root);
    QStringList str;
    str << "*";
    QFileInfoList list = rootDir.entryInfoList(str);
    showFileInfoList(list);
}

void FileView::slotShow(QDir dir)
{
    QStringList str;
    str << "*";
    QFileInfoList list = dir.entryInfoList(str, QDir::AllEntries, QDir::DirsFirst);
    // QDir::AllEntries表示列出文件，目录，磁盘驱动器
    showFileInfoList(list);
}

void FileView::slotDirShow(QListWidgetItem* item)
{
    QString str = item->text(); // 下一级目录的名称
    QDir dir(fileLineEdit->text());
    dir.cd(str);
    fileLineEdit->setText(dir.absolutePath());
    slotShow(dir);
}

// 该函数实现了展示某级目录的所有文件
void FileView::showFileInfoList(QFileInfoList list)
{
    fileListWidget->clear();
    for (int i = 0; i < list.count(); ++i) {
        QFileInfo tmpfileInfo = list.at(i);
        if (tmpfileInfo.isDir()) {
            QIcon icon("../11/dir.png");
            QString filename = tmpfileInfo.fileName();
            QListWidgetItem* item = new QListWidgetItem(icon,filename);
            fileListWidget->addItem(item);
        }else if(tmpfileInfo.isFile()){
            QIcon icon("../11/file.png");
            QString filename = tmpfileInfo.fileName();
            QListWidgetItem* item = new QListWidgetItem(icon,filename);
            fileListWidget->addItem(item);
        }
    }
}


FileView::~FileView()
{
}

