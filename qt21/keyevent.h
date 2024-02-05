#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>

class KeyEvent : public QWidget
{
    Q_OBJECT

public:
    KeyEvent(QWidget* parent = nullptr);
    ~KeyEvent();
    void drawPix();
    void keyPressEvent(QKeyEvent* e);
    void paintEvent(QPaintEvent* e);

private:
    QPixmap* pix; // 充当一个绘图设备
    QImage image;
    int startX, startY, width, height, step;
};
#endif // KEYEVENT_H
