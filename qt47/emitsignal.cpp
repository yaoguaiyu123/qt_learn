#include "emitsignal.h"
#include <QDebug>
#include <QTimer>

EmitSIgnal::EmitSIgnal(QObject* parent)
    : QThread(parent)
{
    qDebug() << "准备发出信号";
}


// 在线程中一直发出信号
void EmitSIgnal::run()
{
    while (true) {
        QThread::sleep(1);
//        emit signal1();   //发出信号
//        emit signal0();   //发出信号
    }
}
