#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//这里不使用头文件，而是使用类声明的方式,仅用来声明该类的指针类型
class QNetworkReply;
class QNetworkAccessManager;

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget* parent = nullptr);
~MainWindow();
private slots:
void replyFinished(QNetworkReply*);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;

};
#endif // MAINWINDOW_H
