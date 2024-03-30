#include "mythread_1.h"
#include <QDebug>

MyThread_1::MyThread_1(int value,QObject *parent)
    :m_value(value)
    ,QThread{parent}
{
    ;
}


void MyThread_1::run()
{
    while (true) {
        qDebug() << m_value;
        QThread::sleep(1);
    }
}
