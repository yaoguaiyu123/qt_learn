#ifndef PAGE02_H
#define PAGE02_H

#include <QWidget>

namespace Ui {
class Page02;
}

class Page02 : public QWidget
{
    Q_OBJECT

public:
    explicit Page02(QWidget *parent = nullptr);
    ~Page02();

private slots:
    void on_pushButton_clicked();
signals:
    void page02Clicked();
private:
    Ui::Page02* ui;

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // PAGE02_H
