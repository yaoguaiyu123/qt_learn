#include "udpclient.h"
#include <QMessageBox>
#include <QHostAddress>

UDPClient::UDPClient(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("UDP客户端");
    receiveTextEdit = new QTextEdit();
    closeBtn = new QPushButton("关闭");
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(receiveTextEdit);
    mainLayout->addWidget(closeBtn);
    resize(500, 400);
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(closeBtnClicked()));
    port = 5555;
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    bool result = udpSocket->bind(5555);
    if (!result) {
        QMessageBox::information(this, "error", "UDP SCOKET 创建失败");
        return;
    }
}

void UDPClient::closeBtnClicked()
{
    close();
}

void UDPClient::dataReceived()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        //pendingDatagramSize()函数是用于获取已接收但尚未读取的待处理数据报文的大小的函数。
        datagram.resize(udpSocket->pendingDatagramSize());
        //QByteArray的data()函数用于获取指向数组首元素的指针。它返回一个可修改的char*指针，可以直接访问和修改QByteArray中的数据。
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString msg = datagram.data();
        receiveTextEdit->insertPlainText(msg);
    }
}


UDPClient::~UDPClient()
{
}

