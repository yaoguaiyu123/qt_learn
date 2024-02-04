#include "udpserver.h"
#include <QHostAddress>

UDPServer::UDPServer(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("UDP服务端");
    timerLabel = new QLabel("计时器:");
    textLineEdit = new QLineEdit(this);
    startBtn = new QPushButton("开始");
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(timerLabel);
    mainLayout->addWidget(textLineEdit);
    mainLayout->addWidget(startBtn);
    resize(200, 150);
    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startBtnClicked()));
    port = 5555;
    isStarted = false;
    udpSocket = new QUdpSocket(this);
    timer = new QTimer(this);
    // 定时发送广播消息
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout())); // 绑定定时器的信号到this->timeout()
}

void UDPServer::startBtnClicked()
{
    if (!isStarted) {
        startBtn->setText("停止");
        timer->start(1000); // 启动定时器
        isStarted = true;
    } else {
        startBtn->setText("开始");
        timer->stop();
        isStarted = false;
    }
}

void UDPServer::timeout()
{
    QString msg = textLineEdit->text();
    int length = 0;
    if (msg == "") {
        return;
    }
    //toLatin1()函数用于将QString对象转换为QByteArray对象,QByteArray对象使用Latin-1编码
    //toUtf8() 函数用于将QString对象转换为QByteArray对象,QByteArray对象使用Utf-8编码
    if ((length = udpSocket->writeDatagram(msg.toUtf8(), QHostAddress::Broadcast, port)) != msg.length()) {
        return;
    }
}

UDPServer::~UDPServer()
{
}

