#ifndef PAGE01_H
#define PAGE01_H

#include <QWidget>

namespace Ui {
class Page01;
}

class Page01 : public QWidget
{
    Q_OBJECT

public:
    explicit Page01(QWidget* parent = nullptr);
    ~Page01();

private slots:
    void on_pushButton_clicked();
signals:
    void page01Clicked();
private:
    Ui::Page01* ui;

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // PAGE01_H
