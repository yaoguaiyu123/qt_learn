#ifndef PHOTOSHOTDIALOG_H
#define PHOTOSHOTDIALOG_H

#include <QWidget>
//裁剪头像活动窗口(范围限制窗口)
//这个窗口设置为透明
#include "cutdialog.h"
#include <QPoint>

class PhotoShotDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoShotDialog(QWidget *parent = nullptr);
    ~PhotoShotDialog();
    QRect getCurrentCutRect();   //获取头像剪切窗口的矩形
private:
    CutDialog* m_cutDialog;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PHOTOSHOTDIALOG_H
