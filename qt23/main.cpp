// Date:2024/2/6
// Author:妖怪鱼
// Introduction:基于控制台的程序(信号量)
// Qt的线程互斥的最基本的QMutex和QMutexLocker的用法见同目录下的image.png
#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include <stdio.h>
#include <iostream>
const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize]; // 生产者向buffer中写入数据，直到终点，然后从起点开始覆盖已经写入的数据
QSemaphore freeBytes(BufferSize); // 表示一开始有80个数据空间可写入
QSemaphore usedBytes(0); // 表示一开始有0个数据可读取

class Producer : public QThread {
public:
    Producer();
    void run();
};

Producer::Producer()
{
    ;
}

void Producer::run()
{
    for (int i = 0; i < DataSize; ++i) {
        // 生产者线程获取一个资源,acquire(n)表示获取n个资源
        freeBytes.acquire(1);
        // 写入数据
        buffer[i % BufferSize] = i % BufferSize;
        // 释放一个资源,release(n)表示释放n个资源
        usedBytes.release(1);
    }
}

class Consumer : public QThread {
public:
    Consumer();
    void run();
};

Consumer::Consumer()
{
    ;
}

void Consumer::run()
{
    for (int i = 0; i < DataSize; ++i) {
        usedBytes.acquire(1);
        std::cout << buffer[i % BufferSize];
        if (i % 16 == 0 && i != 0) {
            std::cout << i << std::endl;
        }
        freeBytes.release(1);
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Producer p;
    Consumer s;
    p.start();
    s.start();
    p.wait();
    s.wait();

    return a.exec();
}
