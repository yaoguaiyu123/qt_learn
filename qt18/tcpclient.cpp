#include "tcpclient.h"
#include <QMessageBox>
#include <QHostInfo>
#include <QDebug>
TcpClient::TcpClient(QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("TCP Client"));
    contentListWidget = new QListWidget;
    sendLineEdit = new QLineEdit;
    sendBtn = new QPushButton(tr("发送"));
    userNameLabel = new QLabel(tr("用户名："));
    userNameLineEdit = new QLineEdit;
    serverIPLabel = new QLabel(tr("服务器地址："));
    serverIPLineEdit = new QLineEdit;
    portLabel = new QLabel(tr("端口："));
    portLineEdit = new QLineEdit;
    enterBtn = new QPushButton(tr("进入聊天室"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget, 0, 0, 1, 2);
    mainLayout->addWidget(sendLineEdit, 1, 0);
    mainLayout->addWidget(sendBtn, 1, 1);
    mainLayout->addWidget(userNameLabel, 2, 0);
    mainLayout->addWidget(userNameLineEdit, 2, 1);
    mainLayout->addWidget(serverIPLabel, 3, 0);
    mainLayout->addWidget(serverIPLineEdit, 3, 1);
    mainLayout->addWidget(portLabel, 4, 0);
    mainLayout->addWidget(portLineEdit, 4, 1);
    mainLayout->addWidget(enterBtn, 5, 0, 1, 2);
    status = false; // 当前状态是未进入聊天室
    port = 8010;
    portLineEdit->setText(QString::number(port));
    serverIP = new QHostAddress();
    connect(enterBtn, SIGNAL(clicked()), this, SLOT(slotEnter()));
    connect(sendBtn, SIGNAL(clicked()), this, SLOT(slotSend()));
    sendBtn->setEnabled(false);
}

// 进入/离开聊天室的函数
void TcpClient::slotEnter()
{
    if (!status) {
        /* 完成输入合法性检验 */
        QString ip = serverIPLineEdit->text();
        if (!serverIP->setAddress(ip)) {
            QMessageBox::information(this, tr("error"), tr("server ip address error!"));
            return;
        }
        if (userNameLineEdit->text() == "") {
            QMessageBox::information(this, tr("error"), tr("User name error!"));
            return;
        }
        userName = userNameLineEdit->text();
        /* 创建了一个QTcpSocket类对象，并将信号/槽连接起来 */
        tcpSocket = new QTcpSocket(this); // 创建一个套接字
        connect(tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
        qDebug() << "客户端用户" << userName << "正在连接服务端";
        tcpSocket->connectToHost(*serverIP, port); // 连接服务端
        status = true;
    } else {
        int length = 0;
        QString msg = userName + tr(":Leave Chat Room");
        if ((length = tcpSocket->write(msg.toUtf8(), msg.length())) != msg.length()) {
            return;
        }
        tcpSocket->disconnectFromHost(); // 断开连接
        status = false; // 将status状态复位
    }
}

void TcpClient::slotConnected()
{
    qDebug() << "客户端用户" << userName << "成功连接服务端";
    sendBtn->setEnabled(true);
    enterBtn->setText(tr("离开"));
    int length=0;
    QString msg=userName+tr(":Enter Chat Room");
    if((length=tcpSocket->write(msg.toLatin1(),msg. length()))!=msg.length())
    {
        return;
    }
}

//发送信息的函数
void TcpClient::slotSend()
{
    if(sendLineEdit->text()=="")
    {
        return ;
    }
    QString msg=userName+":"+sendLineEdit->text();
    tcpSocket->write(msg.toLatin1(),msg.length());
    sendLineEdit->clear();
}

void TcpClient::slotDisconnected()
{
    sendBtn->setEnabled(false);
    enterBtn->setText(tr("进入聊天室"));
}

void TcpClient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(datagram.data(),datagram.size());
        QString msg=datagram.data();
        contentListWidget->addItem(msg.left(datagram.size()));
    }
}

TcpClient::~TcpClient()
{

}
