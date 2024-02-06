// Date:2024/2/6
// Author:妖怪鱼
// Introduction:线程等待和唤醒
#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include <QThread>
#include <stdio.h>
#include <iostream>
const int DataSize = 1000;
const int BufferSize = 80;
int buffer[BufferSize];
QWaitCondition bufferEmpty;
QWaitCondition bufferFull;
QMutex mutex;
int numUsedBytes = 0; // numUsedBytes表示存在多少个可读字节
int rIndex = 0;

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
        mutex.lock();
        if (numUsedBytes == BufferSize) {
            bufferEmpty.wait(&mutex); // 如果已经满了，使当前线程等待
        }
        buffer[i % BufferSize] = i % BufferSize; // 写入数据
        ++numUsedBytes;
        bufferFull.wakeAll();
        mutex.unlock();
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
    forever // 相当于while(true)
    {
        mutex.lock();
        if (numUsedBytes == 0) {
            bufferFull.wait(&mutex);
        }
        //        printf("%d", buffer[rIndex]);
        std::cout << buffer[rIndex];
        if (rIndex % 16 == 0 && rIndex != 0) {
            std::cout << std::endl;
        }
        rIndex = ((rIndex + 1) % BufferSize);
        --numUsedBytes;
        bufferEmpty.wakeAll();
        mutex.unlock();
    }
}

int main(int argc, char *argv[])
{
    //printf在多线程下无法打印
    QCoreApplication a(argc, argv);
    Producer producer;
    Consumer consumer;
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();
    return a.exec();
}
