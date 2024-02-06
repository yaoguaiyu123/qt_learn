#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#define MAXSIZE 3

class WorkThread : public QThread
{
public:
    WorkThread();

protected:
    void run();

};

#endif // WORKTHREAD_H
