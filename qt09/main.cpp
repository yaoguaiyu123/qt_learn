// Date:2024/2/2
// Author:妖怪鱼
// Introduction:Qt文件学习
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtDebug>
#include <QDataStream>
#include <QDate>
#include <QDir>
#include <QStringList>

// QFile类直接读写文本
void test01()
{
    QFile file1("../09/test01.txt");
    if (file1.open(QIODevice::ReadOnly)) { // 只读方式打开文件
        char buffer[2048];
        qint64 lineLen = file1.readLine(buffer, sizeof(buffer)); // qint相当于long long
        if (lineLen != -1) {
            qDebug() << buffer;
        }
    }

    QFile file2("../09/test02.txt");
    if (file2.open(QIODevice::ReadWrite)) { // 读写方式打开文件
        QByteArray data = "hello world!!!!";
        qint64 res = file2.write(data);
        if (res == -1) {
            qDebug() << "写入失败";
        }
    }
}

// QTextStream类读写文本
void test02()
{
    QFile file1("../09/test03.txt");
    if (file1.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file1);
        out << QObject::tr("你好世界") << qSetFieldWidth(10) << 90;
    }

    QFile file2("../09/test01.txt");
    if (file2.open(QIODevice::ReadOnly)) {
        QTextStream in(&file2);
        QString str;
        in >> str;
        qDebug() << str;
    }
}

// 读写二进制文件
void test03()
{
    QFile file1("../09/test04.dat");
    if (file1.open(QFile::ReadWrite | QFile::Truncate)) {
        // 写数据
        QDataStream stream(&file1);
        stream << QString("你好世界");
        stream << QDate::fromString("2004/07/17", "yyyy/MM/dd");
        stream << (qint32)19;
        // 移动文件指针到文件开头(读写数据是同一个文件指针)
        file1.seek(0);
        // 读数据
        QString name;
        QDate date;
        qint32 age;
        stream >> name >> date >> age;
        qDebug() << name << "   " << date << "   " << age;
    }
}

//目录操作与文件操作
void test04()
{
    QDir dir(path);
    qint64 size = 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //    test01();
    //    test02();
//    test03();
    return a.exec();
}









