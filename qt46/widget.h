#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "mythread_1.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton *button1, *button2;
    MyThread_1 *thread1, *thread2, *thread3, *thread4;
private slots:
    void on_button1_clicked();
    void on_button2_clicked();
};
#endif // WIDGET_H
