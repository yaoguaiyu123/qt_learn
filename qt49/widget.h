#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
class QPushButton;
class QScreen;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void grapSreen();

private:
    QScreen* m_screen;
    QPixmap m_pixmap;
    QPushButton* m_pushbutton1;
    QLabel* m_label;
};
#endif // WIDGET_H
