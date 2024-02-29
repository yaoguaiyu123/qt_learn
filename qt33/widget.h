#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QQCell;

class Widget : public QWidget
{
    Q_OBJECT

public:
Widget(QWidget *parent = nullptr);
~Widget();
private slots:
void sltCellStatusChange(QWidget*);

private:
QQCell *m_cell1, *m_cell;
};
#endif // WIDGET_H
