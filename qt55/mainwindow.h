#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class topWidget;
}
QT_END_NAMESPACE
class Client;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::topWidget* ui;
};
#endif // MAINWINDOW_H
