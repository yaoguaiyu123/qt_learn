#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    QStringList drivers = QSqlDatabase::drivers(); // 返回一个支持的数据库驱动程序的列表(如果系统上安装了该驱动的话)
    ui->comboBox->addItems(drivers);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(driverChanged(const QString&)));
    ui->status_label->setText("准备连接数据库");
    connect(ui->pushButton_1, SIGNAL(clicked(bool)), this, SLOT(clickedButton1()));
}

void ConnectDialog::driverChanged(const QString& text)
{
    if (text == "QSQLITE") {
        ui->lineEdit_1->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->spinBox->setEnabled(false);
    } else {
        ui->lineEdit_1->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->spinBox->setEnabled(true);
    }
}

QString ConnectDialog::driverName() const
{
    return ui->comboBox->currentText();
}

QString ConnectDialog::databaseName() const
{
    return ui->lineEdit_1->text();
}

QString ConnectDialog::userName() const
{
    return ui->lineEdit_2->text();
}

QString ConnectDialog::password() const
{
    return ui->lineEdit_3->text();
}

QString ConnectDialog::hostName() const
{
    return ui->lineEdit_4->text();
}

int ConnectDialog::port() const
{
    return ui->spinBox->value();
}

// 连接按钮点击
void ConnectDialog::clickedButton1()
{
    if (ui->comboBox->currentText().isEmpty()) {
        ui->status_label->setText("请选择一个数据库驱动!!");
        ui->comboBox->setFocus();
    } else if (ui->comboBox->currentText() == "QSQLITE") {
        addSqliteConnection();
        creatDB();
        accept(); // 接收用户操作并关闭对话框
    } else {
        // 尝试使用其他方式连接数据库
        QSqlError err = addConnection(driverName(), databaseName(), hostName(), userName(), password(), port()); //(d)
        if (err.type() != QSqlError::NoError) {
            ui->status_label->setText(err.text());
        } else {
            accept();
        }
    }
}

// 建立一条数据库连接
// 连接远程的数据库
QSqlError ConnectDialog::addConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, int port)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
    }
    return err;
}

// 建立一条sqlite数据库连接
// 创建一个sqlite数据库
void ConnectDialog::addSqliteConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testDatabase01");  //设置数据库的名称为 "testDatabase01"，即将要创建或打开的数据库文件的名称。
    if (!db.open()) {
        ui->status_label->setText(db.lastError().text());
        return;
    }
    ui->status_label->setText(tr("创建sqlite数据库成功!"));
}

// 初始化两张数据库表
void ConnectDialog::creatDB()
{
    QSqlQuery query;
    query.exec("create table factory (id int primary key,manufactory varchar(40), address varchar(40))");				//(b)
    query.exec(QObject::tr("insert into factory values(1, '一汽大众', '长春')"));
    query.exec(QObject::tr("insert into factory values(2, '二汽神龙', '武汉')"));
    query.exec(QObject::tr("insert into factory values(3, '上海大众', '上海')"));
    //这里创建了一个外键
    query.exec("create table cars (carid int primary key, name varchar(50), factoryid int, year int, foreign key(factoryid) references factory(id))");	//(c)
    query.exec(QObject::tr("insert into cars values(1,'奥迪A6',1,2005)"));
    query.exec(QObject::tr("insert into cars values(2, '捷达', 1, 1993)"));
    query.exec(QObject::tr("insert into cars values(3, '宝来', 1, 2000)"));
    query.exec(QObject::tr("insert into cars values(4, '毕加索',2, 1999)"));
    query.exec(QObject::tr("insert into cars values(5, '富康', 2, 2004)"));
    query.exec(QObject::tr("insert into cars values(6, '标致307',2, 2001)"));
    query.exec(QObject::tr("insert into cars values(7, '桑塔纳',3, 1995)"));
    query.exec(QObject::tr("insert into cars values(8, '帕萨特',3, 2000)"));
}
