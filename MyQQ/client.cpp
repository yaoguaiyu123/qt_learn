#include "client.h"
#include "ui_client.h"

#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    setFixedSize(400,190);

    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tClnt = new QTcpSocket(this);  //创建TCP套接字
    tPort = 5555;
    connect(tClnt, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(tClnt, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(displayErr(QAbstractSocket::SocketError)));

    connect(ui->cCloseBtn, SIGNAL(clicked(bool)), this, SLOT(cCloseBtn_clicked()));
    connect(ui->cCancleBtn, SIGNAL(clicked(bool)), this, SLOT(cCancleBtn_clicked()));
}

Client::~Client()
{
    delete ui;
}

void Client::setFileName(QString name)
{
    locFile = new QFile(name);  //通过文件的地址创建一个文件
}

void Client::setHostAddr(QHostAddress addr)
{
    hostAddr = addr;
    newConn();
}

//客户端连接到服务端
void Client::newConn()
{
    blockSize = 0;
    tClnt->abort();
    tClnt->connectToHost(hostAddr, tPort);
    time.start();  //开启计时器
}

//接收文件
//当客户端接收到信息的时候就会调用此函数
void Client::readMsg()
{
    QDataStream in(tClnt);   //创建一个字节流

    float useTime = time.elapsed();   //获取时间节点

    //判断当前接收的内容是不是还是文件头的内容
    if (bytesReceived <= sizeof(qint64)*2) {
        //bytesAvailable() 获取当前 QTcpSocket 接收缓冲区中可读取的字节数量
        //fileNameSize 表示文件名的大小
        if ((tClnt->bytesAvailable() >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            //接收文件头中的 文件总大小和文件名大小
            in>>totalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tClnt->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            //接收文件头中的 文件名
            in>>fileName;
            bytesReceived +=fileNameSize;
            //打开文件对象准备写入
            if(!locFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.").arg(fileName).arg(locFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }

    if (bytesReceived < totalBytes) {
        bytesReceived += tClnt->bytesAvailable();
        inBlock = tClnt->readAll();   //读取所有TCP缓冲区中的数据
        locFile->write(inBlock);    //将数据写入到文件
        inBlock.resize(0);
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->cStatusLbl->setText(tr("已接收 %1MB (%2MB/s) \n共%3MB 已用时：%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(totalBytes / (1024 * 1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(totalBytes/speed/1000 - useTime/1000,0,'f',0));

    if(bytesReceived == totalBytes)
    {
        locFile->close();   //关闭文件
        tClnt->close();     //关闭TCP套接字
        ui->cStatusLbl->setText(tr("接收文件 %1 完毕").arg(fileName));
    }
}

//显示错误
void Client::displayErr(QAbstractSocket::SocketError sockErr)
{
    switch(sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError : break;
    default : qDebug() << tClnt->errorString();
    }
}

void Client::cCancleBtn_clicked()
{
    tClnt->abort();
    if (locFile->isOpen())
        locFile->close();
}

void Client::cCloseBtn_clicked()
{
    tClnt->abort();
    if (locFile->isOpen())
        locFile->close();
    close();
}

void Client::closeEvent(QCloseEvent *)
{
    cCloseBtn_clicked();
}
