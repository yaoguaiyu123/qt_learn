#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class LineEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    LineEdit* lineEdit;

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};
#endif // WIDGET_H
