#ifndef WIDGET_H
#define WIDGET_H

//界面类

#include "AudioInput.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
private:

    QThread *_imgThread;
    QThread *_textThread;

    void removePartner(quint32);
    void clearPartner(); //退出会议，或者会议结束
    void closeImg(quint32); //根据IP重置图像

    //音频
    AudioInput* _ainput;
    QThread* _ainputThread;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

};
#endif // WIDGET_H
