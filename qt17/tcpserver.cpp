#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("TCP服务端");
    contentListWidget = new QListWidget();
    portLabel = new QLabel("端口:");
    portLineEdit = new QLineEdit();
    createBtn = new QPushButton("创建聊天室");
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(portLabel,1,0);
    mainLayout->addWidget(portLineEdit,1,1);
    mainLayout->addWidget(createBtn,2,0,1,2);
    port = 8010;
    portLineEdit->setText(QString::number(port));
    connect(createBtn, SIGNAL(clicked(bool)), this, SLOT(slotCreateServer()));
}

void TcpServer::slotCreateServer()
{
    server = new Server(this, port);
    connect(server, SIGNAL(updateServer(QString, int)), this, SLOT(updateServer(QString, int)));
    createBtn->setEnabled(false);
}

//更新服务端的窗口内容
void TcpServer::updateServer(QString msg, int length){
    contentListWidget->addItem(msg.left(length));
}

TcpServer::~TcpServer()
{
}

