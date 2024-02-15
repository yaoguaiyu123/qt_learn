#include "mainwindow.h"
#include <QGridLayout>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QDialog>
#include <QDebug>

MainWindow::MainWindow(const QString &factoryTable,const QString &carTable,QFile *carDetails,QWidget *parent)
    : QMainWindow(parent)
{
    // 初始化数据
    file = carDetails;  //初始化文件对象
    readCarData();    //将XML文件中的内容读入到QDomDocument类实例carData中
    carModel = new QSqlRelationalTableModel(this);
    carModel->setTable(carTable);    //设置carModel对应的数据库表为carTable
    //setRelation函数设置表中的某一列与另一个表的关联关系
//    这里指定了carTable表的第二个字段与factoryTable表的id字段相映射，并且在模型视图中显示为manufactory字段
    carModel->setRelation(2, QSqlRelation(factoryTable, "id", "manufactory"));
    carModel->select();   //执行查询
    factoryModel = new QSqlTableModel(this);
    //执行setTable和select两个函数相当于select * from testTable
    factoryModel->setTable(factoryTable);
    factoryModel->select();

    QGroupBox* factory = createFactoryGroupBox();
    QGroupBox* cars = createCarGroupBox();
    QGroupBox* details = createDetailsGroupBox();
    // 布局
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(factory, 0, 0);
    layout->addWidget(cars, 1, 0);
    layout->addWidget(details, 0, 1, 2, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(0, 500);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);
    createMenuBar();
    resize(850, 400);
    setWindowTitle("主从视图");
}

QGroupBox* MainWindow::createFactoryGroupBox()
{
    factoryView = new QTableView();
    factoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止编辑单元格内容
    factoryView->setSortingEnabled(true);       //允许用户对表格内容进行排序
    factoryView->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置选中单元格时会选中整行数据
    factoryView->setSelectionMode(QAbstractItemView::SingleSelection);  //单选
    factoryView->setShowGrid(false);  //不显示网格线
    factoryView->setAlternatingRowColors(true);   //表格将显示为行颜色交替
    factoryView->setModel(factoryModel);
    connect(factoryView,SIGNAL(clicked (QModelIndex )),this,SLOT(changeFactory(QModelIndex)));
    QGroupBox* box = new QGroupBox("汽车制造商");
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(factoryView, 0, 0);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createCarGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("汽车"));
    carView = new QTableView;
    carView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    carView->setSortingEnabled(true);
    carView->setSelectionBehavior(QAbstractItemView::SelectRows);
    carView->setSelectionMode(QAbstractItemView::SingleSelection);
    carView->setShowGrid(false);
    carView->verticalHeader()->hide();
    carView->setAlternatingRowColors(true);
    carView->setModel(carModel);
    connect(carView, SIGNAL(clicked(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
    connect(carView, SIGNAL(activated(QModelIndex)),this,SLOT(showCarDetails(QModelIndex)));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(carView);
    box->setLayout(layout);
    return box;
}

QGroupBox* MainWindow::createDetailsGroupBox()
{
    QGroupBox *box = new QGroupBox(tr("详细信息"));
    profileLabel = new QLabel;
    profileLabel->setWordWrap(true);    //当文本宽度超过控件宽度，自动换行显示
    profileLabel->setAlignment(Qt::AlignBottom);  //设置 QLabel 对象的文本对齐方式为底部对齐
    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignBottom);
    attribList = new QListWidget;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(profileLabel, 0, 0, 1, 2);
    layout->addWidget(titleLabel, 1, 0, 1, 2);
    layout->addWidget(attribList, 2, 0, 1, 2);
    layout->setRowStretch(2, 1);
    box->setLayout(layout);
    return box;
}

//创建操作菜单
void MainWindow::createMenuBar()
{
    QAction *addAction = new QAction(tr("添加"), this);
    QAction *deleteAction = new QAction(tr("删除"), this);
    QAction *quitAction = new QAction(tr("退出"), this);
    addAction->setShortcut(tr("Ctrl+A"));
    deleteAction->setShortcut(tr("Ctrl+D"));
    quitAction->setShortcut(tr("Ctrl+Q"));
    QMenu *fileMenu = menuBar()->addMenu(tr("操作菜单"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    connect(addAction, SIGNAL(triggered(bool)), this, SLOT(addCar()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(delCar()));
    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

// 在表格中点击制造商执行该函数
void MainWindow::changeFactory(QModelIndex index)
{
    // QModelIndex表示数据模型中项的索引，包括行号，列号等信息
    QSqlRecord record = factoryModel->record(index.row()); // 取出数据库表中的记录(行)
    QString factoryId = record.value("id").toString();
    carModel->setFilter("id = '" + factoryId + "'"); // 在汽车模型中设置过滤器，只显示对应制造商的汽车
    showFactorytProfile(index); // 显示汽车制造商的详细信息
}

// 显示汽车制造商详细信息
void MainWindow::showFactorytProfile(QModelIndex index)
{
    QSqlRecord record = factoryModel->record(index.row()); // 取出数据库表中的记录(行)
    QString name = record.value("manufactory").toString();
    int count = carModel->rowCount();
    profileLabel->setText(tr("汽车制造商:%1\n产品数量:%2").arg(name).arg(count));
    profileLabel->show();
    titleLabel->hide();
    attribList->hide();
}

// 显示汽车详细信息
void MainWindow::showCarDetails(QModelIndex index)
{
    QSqlRecord record = carModel->record(index.row()); // 取出数据库表中的记录(行)
    QString factory = record.value("manufactory").toString();
    QString name = record.value("name").toString();
    QString year = record.value("year").toString();
    QString carId = record.value("carId").toString();
    qDebug() << "name: " << name << "   year: " << year;
    showFactorytProfile(indexOfFactory(factory)); // 通过car的manufactory得到factory的index然后显示汽车制造商信息
    titleLabel->setText(tr("品牌%1(%2)").arg(name).arg(year));
    titleLabel->show();
    QDomNodeList cars = carData.elementsByTagName("car");
    for (int i = 0; i < cars.count(); i++) // 找出所有car标签
    {
        QDomNode car = cars.item(i);
        if (car.toElement().attribute("id") == carId)
        {
            getAttribList(car.toElement());  //显示car标签的相关信息
            break;
        }
    }
    if (!attribList->count() == 0) {
        attribList->show();
    }
}

//从QDomNode中读取数据
void MainWindow::getAttribList(QDomNode car)
{
    attribList->clear();
    QDomNodeList attribs = car.childNodes();
    QDomNode node;
    QString attribNumber;
    for (int j = 0; j < attribs.count(); j++)
    {
        node = attribs.item(j);
        attribNumber = node.toElement().attribute("number");
        QListWidgetItem *item = new QListWidgetItem(attribList);
        QString showText(attribNumber + ": " + node.toElement().text());
        item->setText(tr("%1").arg(showText));
    }
}

//删除一辆汽车的函数
void MainWindow::delCar()
{
    QModelIndexList selection = carView->selectionModel() ->selectedRows(0);
    if (!selection.empty())
    {
        QModelIndex idIndex = selection.at(0);
        int id = idIndex.data().toInt();
        QString name = idIndex.sibling(idIndex.row(), 1).data(). toString();
        QString factory = idIndex.sibling(idIndex.row(), 2).data(). toString();
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("删除汽车记录"),
            QString(tr("确认删除由'%1'生产的'%2'吗？").arg(factory).arg
            (name)),QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::Yes)	 	//得到用户确认
        {
            removeCarFromFile(id);			//从XML文件中删除相关内容
            removeCarFromDatabase(idIndex);	//从数据库表中删除相关内容
            decreaseCarCount(indexOfFactory(factory));
        }
        else														//(d)
        {
            QMessageBox::information(this, tr("删除汽车记录"),tr("请选择要删除的记录。"));
        }
    }
}

//从XML文件中删除car
void MainWindow::removeCarFromFile(int id)
{
    QDomNodeList cars = carData.elementsByTagName("car");
    for (int i = 0; i< cars.count(); i++)
    {
        QDomNode node = cars.item(i);
        if (node.toElement().attribute("id").toInt() == id)
        {
            carData.elementsByTagName
                ("archive").item(0).removeChild(node);
            break;
        }
    }
}

void MainWindow::removeCarFromDatabase(QModelIndex index)
{
    carModel->removeRow(index.row());
}

void MainWindow::decreaseCarCount(QModelIndex index)
{
    int row = index.row();
    int count = carModel->rowCount();
    if (count == 0)
        factoryModel->removeRow(row);
}

void MainWindow::readCarData()
{
    if (!file->open(QIODevice::ReadOnly))
        return;
    if (!carData.setContent(file))
    {
        file->close();
        return;
    }
    file->close();
}

QModelIndex MainWindow::indexOfFactory(const QString &factory)
{
    for (int i = 0; i < factoryModel->rowCount(); i++)
    {
        QSqlRecord record =  factoryModel->record(i);
        if (record.value("manufactory") == factory)
            return factoryModel->index(i, 1);
    }
    return QModelIndex();
}

//void MainWindow::addCar()
//{
//    Dialog *dialog = new Dialog(carModel, factoryModel,carData, file, this);
//    int accepted = dialog->exec();
//    if (accepted == 1)
//    {
//        int lastRow = carModel->rowCount() - 1;
//        carView->selectRow(lastRow);
//        carView->scrollToBottom();
//        showCarDetails(carModel->index(lastRow, 0));
//    }
//}

MainWindow::~MainWindow()
{
}

