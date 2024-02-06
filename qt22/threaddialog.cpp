#include "threaddialog.h"
#include <QHBoxLayout>

ThreadDialog::ThreadDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("线程");
    startBtn = new QPushButton("开始");
    stopBtn = new QPushButton("停止");
    quitBtn = new QPushButton("退出");
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(stopBtn);
    mainLayout->addWidget(quitBtn);
    connect(stopBtn, SIGNAL(clicked(bool)), this, SLOT(slotStop()));
    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(slotStart()));
    connect(quitBtn, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void ThreadDialog::slotStart()
{
    for (int i = 0; i < MAXSIZE; ++i) {
        workedThread[i] = new WorkThread();
    }
    for (int i = 0; i < MAXSIZE; ++i) {
        workedThread[i]->start();
    }
    startBtn->setEnabled(false);
    stopBtn->setEnabled(true);
}

void ThreadDialog::slotStop()
{
    for (int i = 0; i < MAXSIZE; ++i) {
        workedThread[i]->terminate();
        workedThread[i]->wait();
    }
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
}

ThreadDialog::~ThreadDialog()
{

}

