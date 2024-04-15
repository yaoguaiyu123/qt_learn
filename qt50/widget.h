#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QLineEdit;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    int m_ans = 0;
    int m_ans_key = 0;
    int m_ans_mouse = 0;
    QLineEdit* lineEdit;
protected:
    virtual bool event(QEvent* event) override;
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent * event) override;
    virtual void mousePressEvent(QMouseEvent * event) override;
    virtual void closeEvent(QCloseEvent * event) override;
};
#endif // WIDGET_H
