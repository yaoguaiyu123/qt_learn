#ifndef THREADDIALOG_H
#define THREADDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "workthread.h"
class ThreadDialog : public QDialog
{
    Q_OBJECT

public:
    ThreadDialog(QWidget* parent = nullptr);
    ~ThreadDialog();
public slots:
    void slotStart();
    void slotStop();
private:
    WorkThread* workedThread[MAXSIZE];   //这个数组指向所启动的全部线程
private:
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* quitBtn;
};
#endif // THREADDIALOG_H
