#include "systemtray.h"
#include "ui_systemtray.h"
#include <QDebug>

SystemTray::SystemTray(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SystemTray)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); // 去掉Qt自带的按钮组件
    m_systemTray = new QSystemTrayIcon(this);
    // QSystemTrayIcon::activated信号在用户与托盘进行交互时发出
    connect(m_systemTray, &QSystemTrayIcon::activated, this, &SystemTray::on_actived);
    m_menu = new QMenu(this);
    m_action1 = new QAction(m_menu);
    m_action2 = new QAction(m_menu);
    m_action3 = new QAction(m_menu);
    m_action4 = new QAction(m_menu);
    m_action1->setText("显示窗口");
    m_action2->setText("显示消息");
    m_action3->setText("显示来电");
    m_action4->setText("退出");
    m_menu->addAction(m_action1);
    m_menu->addAction(m_action2);
    m_menu->addAction(m_action3);
    m_menu->addAction(m_action4);
    connect(m_action1, &QAction::triggered, this, &SystemTray::on_action1);
    connect(m_action2, &QAction::triggered, this, &SystemTray::on_action2);
    connect(m_action3, &QAction::triggered, this, &SystemTray::on_action3);
    connect(m_action4, &QAction::triggered, this, &SystemTray::on_action4);
    m_systemTray->setContextMenu(m_menu);
}

SystemTray::~SystemTray()
{
    delete ui;
}


void SystemTray::on_toolButton_clicked()
{
    // 显示托盘
    QIcon icon = QIcon(":/images/app.png");
    m_systemTray->setIcon(icon);
    m_systemTray->setToolTip("测试托盘显示");
    m_systemTray->show();
    this->hide();
}

void SystemTray::on_actived(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Context: // 右击
        qDebug() << "右击";
        // 右击显示菜单，但是m_systemTray->setContextMenu(m_menu);之后不用在这边设置也能右击显示
        break;
    case QSystemTrayIcon::Trigger: // 左击
        qDebug() << "左击";
        showWindow();
        break;

    default:
        break;
    }
}


// 显示窗口的函数
void SystemTray::showWindow()
{
    this->show();
}

// 关闭按钮
void SystemTray::on_pushButton_clicked()
{
    close();
}

void SystemTray::on_action1()
{
    qDebug() << "action1";
}

void SystemTray::on_action2()
{
    qDebug() << "action2";
    m_systemTray->showMessage("提示", "这是一个消息", QSystemTrayIcon::Information, 5000);
}

void SystemTray::on_action3()
{
    qDebug() << "action3";
}

void SystemTray::on_action4()
{
    qDebug() << "action4";
    qApp->quit();
}


