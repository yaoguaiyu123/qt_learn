#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QTableView>
#include <QListWidget>
#include <QLabel>
#include <QFile>
#include <QDomNode>
#include <QDomDocument>
#include <QSqlRelationalTableModel>

//QSqlQueryModel可以作为数据源在Qt视图类中表示，这里使用QTable类表示
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &factoryTable,const QString &carTable,QFile *carDetails,QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGroupBox* createCarGroupBox();
    QGroupBox* createFactoryGroupBox();
    QGroupBox* createDetailsGroupBox();
    void createMenuBar();
    QTableView* carView;  //显示汽车的视图
    QTableView* factoryView;   //显示制造商的视图
    QListWidget* attribList;    //显示车型详细信息的列表
    QLabel* profileLabel;
    QLabel* titleLabel;

    void decreaseCarCount(QModelIndex index);
    void getAttribList(QDomNode car);
    QModelIndex indexOfFactory(const QString &factory);
    void readCarData();
    void removeCarFromDatabase(QModelIndex index);
    void removeCarFromFile(int id);

    QDomDocument carData;
    QFile *file;
    QSqlRelationalTableModel *carModel;
    QSqlTableModel *factoryModel;
private slots:
//    void addCar();
    void changeFactory(QModelIndex index);
    void delCar();
    void showCarDetails(QModelIndex index);
    void showFactorytProfile(QModelIndex index);

};
#endif // MAINWINDOW_H
