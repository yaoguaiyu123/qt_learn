#ifndef MYTHREAD_1_H
#define MYTHREAD_1_H

#include <QThread>

class MyThread_1 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread_1(int value ,QObject *parent = nullptr);
protected:
    void run();

private:
    int m_value;
};

#endif // MYTHREAD_1_H
