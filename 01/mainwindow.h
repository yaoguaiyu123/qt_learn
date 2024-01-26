#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget* parent = nullptr);
QLabel *label1, *label2;
QLineEdit* lineEdit;
QPushButton* button;

~MainWindow();
private slots:
void showArea();

};
#endif // MAINWINDOW_H
