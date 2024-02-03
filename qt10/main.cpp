// Date:2024/2/3
// Author:妖怪鱼
// Introduction:文件大小及路径获取实例
#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QtDebug>
qint64 du(const QString& path)
{
    QDir dir(path);
    qint64 size = 0;
    //entryInfoList表示以列表的形式返回一个目录中所有文件信息
    //QDir::Files表示过滤，普通文件通过过滤，子目录则不通过过滤
    foreach (QFileInfo fileinfo, dir.entryInfoList(QDir::Files)) {
        size += fileinfo.size();
    }
    //entryList表示以列表的形式返回一个目录中所有文件名称
    //QDir::Dirs表示过滤，普通文件不通过过滤，子目录通过过滤
    //QDir::NoDotAndDotDot 表示在结果列表中不包括当前目录（"."）和上级目录（".."）的名称。
    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        size += du(path + QDir::separator() + subDir);
    }
    // 进行单位转换
    QString unit = "B";
    qint64 curSize = size;
    if (curSize > 1024) {
        curSize /= 1024;
        unit = "KB";
        if (curSize > 1024) {
            curSize /= 1024;
            unit = "MB";
            if (curSize > 1024) {
                curSize /= 1024;
                unit = "GB";
            }
        }
    }
    //qPrintable() 是一个用于将 QString 或 QByteArray 转换为 C 风格字符串的宏。
    qDebug() << curSize << unit << "\t" << qPrintable(path);
    return size;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path("/run/media/root/study/软件构成资料/22级考试");
    qDebug() << "当前路径:" << path;
    du(path);
    return a.exec();
}
