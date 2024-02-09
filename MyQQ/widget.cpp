#include "widget.h"
#include "ui_widget.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QDebug>
#include <QFileDialog>


Widget::Widget(QWidget *parent,QString username) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->username = username;
    // 创建UdpSocket在7979端口监听
    // QUdpSocket::ShareAddress表示允许其他套接字绑定到相同的端口号
    // QUdpSocket::ReuseAddressHint提供了一个提示，表明如果地址已经在使用中，操作系统应该考虑允许重新使用地址。
    udpSocket = new QUdpSocket(this);
    port = 7979;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendBtn_clicked()));
    connect(ui->sendTBtn, SIGNAL(clicked()), this, SLOT(sendTBtn_clicked()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    sendMsg(UsrEnter);  //发送消息:用户进入群聊,这条发送的消息也会被自己接收

    srv = new Server(this);
    connect(srv, SIGNAL(sendFileName(QString)), this, SLOT(getFileName(QString)));

    //初始化按钮图标
    ui->sendTBtn->setIcon(QPixmap(":/images/send.png"));
}

// 发送消息
void Widget::sendMsg(MsgType type, QString srvaddr)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString address = getIp();
    out << type << getUsername();
    switch (type) {
    case Msg:
        if (ui->msgTextEdit->toPlainText() == "") {
            QMessageBox::warning(nullptr, "警告", "发送的内容不能为空", QMessageBox::Ok);
            return;
        }
        out << address << getMessage();
        ui->msgBrowser->verticalScrollBar()->setValue(ui->msgBrowser->verticalScrollBar()->maximum());
        break;
    case UsrEnter:
//        qDebug() << "发送新用户加入信息:" << getUsername() << "   " << address;
        out << address;
        break;
    case UsrLeft:
        break;
    case FileName: {
        int row = ui->userTableWidget->currentRow();
        QTableWidgetItem* item01 = ui->userTableWidget->item(row, 1);
        QString clntaddr = item01->text();
        qDebug() << clntaddr;
        out << address << clntaddr << filename;
        break;
    }
    case Refuse:
        out << srvaddr;
        break;
    }
    // P2P模式下所有的主机对应的程序都在同一端口监听和发送
    // QHostAddress::Broadcast表示广播地址，用于向同一网络中所有设备发送数据
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, port);
}

// 接收消息
void Widget::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray dataGram;
        dataGram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(dataGram.data(), dataGram.size());
        QDataStream in(&dataGram, QIODevice::ReadOnly);
        int msgType;
        in >> msgType;
        QString usrname, ipAddr, msg;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间
        switch (msgType) {
        case Msg:
            in >> usrname >> ipAddr >> msg;
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
            ui->msgBrowser->append("[" + usrname + "]" + time);
            ui->msgBrowser->append(msg);
            break;
        case UsrEnter:
            in >> usrname >> ipAddr;
//            qDebug() << "接收到新用户加入:" << usrname << "   " << ipAddr;
            userEnter(usrname, ipAddr);
            break;
        case UsrLeft:
            in >> usrname;
            userLeft(usrname, time);
            break;
        case FileName:{
            in >> usrname >> ipAddr;
            QString clntAddr, fileName;
            in >> clntAddr >> fileName;
            hasPendingFile(usrname, ipAddr, clntAddr, fileName);
            break;
        }
        case Refuse: {
            in >> usrname;
            QString srvAddr;
            in >> srvAddr;
            QString ipAddr1 = getIp();

            if (ipAddr1 == srvAddr) {
                srv->refused();
            }
            break;
        }
        }
    }
}

// 处理新用户加入
void Widget::userEnter(QString username, QString ipaddr)
{
    bool isEmpty = ui->userTableWidget->findItems(username, Qt::MatchExactly).isEmpty();
    if (isEmpty) {
        QTableWidgetItem* user = new QTableWidgetItem(username);
        QTableWidgetItem* ip = new QTableWidgetItem(ipaddr);
        ui->userTableWidget->insertRow(0); // 插入一行
        ui->userTableWidget->setItem(0, 0, user);
        ui->userTableWidget->setItem(0, 1, ip);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->msgBrowser->append(tr("%1 在线!").arg(username));
        ui->userNumLabel->setText(tr("在线人数:%1").arg(ui->userTableWidget->rowCount()));
        sendMsg(UsrEnter); // 这是告诉新加入的用户当前的在线用户有哪些
    }
}

void Widget::userLeft(QString username, QString time)
{
    // 获得对应的用户在userTableWidget中的行号
    int rowNum = ui->userTableWidget->findItems(username, Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->msgBrowser->append(tr("%1 于 %2离开!").arg(username).arg(time));
    ui->userNumLabel->setText(tr("在线人数:%1").arg(ui->userTableWidget->rowCount()));
}

QString Widget::getIp()
{
    // 获取本机上所有的IP地址，并返回第一个IPv4地址。
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress a, list) {
        if (a.protocol() == QAbstractSocket::IPv4Protocol) {
            return a.toString();
        }
    }
    return "";
}

QString Widget::getUsername()
{
    return this->username;
}

QString Widget::getMessage()
{
    QString msg = ui->msgTextEdit->toPlainText(); // 返回输入框中的内容
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
    return msg;
}

// 点击了发送按钮
void Widget::sendBtn_clicked()
{
    sendMsg(Msg);
}

//点击了发送文件按钮
void Widget::sendTBtn_clicked()
{
    if(ui->userTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("选择用户"),tr("请先选择目标用户！"), QMessageBox::Ok);
        return;
    }
    srv->show();
    srv->initSrv();
}


void Widget::getFileName(QString name)
{
    filename = name;
    sendMsg(FileName);
}

//处理是否接收文件的函数
void Widget::hasPendingFile(QString usrname, QString srvaddr,QString clntaddr, QString filename)
{
    QString ipAddr = getIp();
    if(ipAddr == clntaddr)
    {
        int btn = QMessageBox::information(this, tr("接受文件"), tr("来自%1(%2)的文件：%3,是否接收？")
                    .arg(usrname).arg(srvaddr).arg(filename), QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),filename);   //处理文件的保存地址
            if(!name.isEmpty())
            {
                Client *clnt = new Client(this);   //创建客户端
                clnt->setFileName(name);
                clnt->setHostAddr(QHostAddress(srvaddr));
                clnt->show();
            }
        } else {
            sendMsg(Refuse, srvaddr);
        }
    }
}




Widget::~Widget()
{
    delete ui;
}
