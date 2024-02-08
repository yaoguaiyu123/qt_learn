#include "server.h"
#include "ui_server.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    //    setFixedSize(400,200);
    tPort = 5555;
    tServer = new QTcpServer(this); // 创建服务端程序
    connect(tServer, SIGNAL(newConnection()), this, SLOT(sndMsg()));
    connect(ui->sSendButton, SIGNAL(clicked(bool)), this, SLOT(sSendBtn_clicked()));
    connect(ui->sCloseButton, SIGNAL(clicked(bool)), this, SLOT(sCloseBtn_clicked()));
    connect(ui->sOpenButton, SIGNAL(clicked(bool)), this, SLOT(sOpenBtn_clicked()));
    initSrv();

}

// 初始化
void Server::initSrv()
{
    payloadSize = 64 * 1024;
    totalBytes = 0;
    bytesWriten = 0;
    bytesTobeWrite = 0;
    ui->sStatusLabel->setText("请选择要传送的文件");
    ui->progressBar->reset();
    ui->sOpenButton->setEnabled(true);
    ui->sSendButton->setEnabled(false);
    tServer->close(); // 关闭服务器
}

// 发送文件
void Server::sndMsg()
{
    ui->sSendButton->setEnabled(false);
    tcpSocket = tServer->nextPendingConnection(); // 从TcpServer获取TcpSocket连接
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));
    ui->sStatusLabel->setText(tr("开始传送文件 %1 !").arg(theFilename));
    localFile = new QFile(filename);
    if (!localFile->open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "应用程序", tr("无法读取文件 %1\n%2").arg(filename).arg(localFile->errorString()));
        return;
    }
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly); // 创建一个写入到缓冲区的字节流
    time.start(); // 启动计时器
    QString curFile = filename.right(filename.size() - filename.lastIndexOf('/') - 1); // 通过文件路径获得文件名
    sendOut << qint64(0) << qint64(0) << curFile; // 构造一个文件头,两个qint64用于存储后续要传输的文件的大小信息
    totalBytes += outBlock.size(); // 加上文件头的大小
    sendOut.device()->seek(0); // 流指针指向开头
    sendOut << totalBytes << qint64(outBlock.size() - sizeof(qint64) * 2);
    bytesTobeWrite = totalBytes - tcpSocket->write(outBlock);
    outBlock.resize(0); // 清空发送缓冲区
}

// 更新进度条并且持续传输文件
void Server::updClntProgress(qint64 numBytes)
{
    qApp->processEvents(); // 使界面不会冻结
    bytesWriten += (int)numBytes;
    if (bytesTobeWrite > 0) {
        outBlock = localFile->read(qMin(bytesTobeWrite, payloadSize)); // 将文件数据读入到缓冲区
        bytesTobeWrite -= (int)tcpSocket->write(outBlock);
        outBlock.reserve(0);
    } else {
        localFile->close();
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWriten);
    float useTime = time.elapsed();
    double speed = bytesWriten / useTime;
    ui->sStatusLabel->setText(tr("已发送 %1MB (%2MB/s) \n共%3MB 已用时:%4s\n 估计剩余时间 %5s")
                                  .arg(bytesWriten / 1024 / 1024)
                                  .arg(speed / 1024 / 1024, 0, 'f', 2)
                                  .arg(totalBytes / 1024 / 1024)
                                  .arg(useTime / 1000, 0, 'f', 0)
                                  .arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));
    if (bytesWriten == totalBytes) {
        localFile->close();
        tServer->close();
        ui->sStatusLabel->setText(tr("传输文件%1成功!").arg(theFilename));
    }
}

void Server::sOpenBtn_clicked()
{
    filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty())
    {
        theFilename = filename.right(filename.size() - filename.lastIndexOf('/')-1);
        ui->sStatusLabel->setText(tr("要传送的文件为：%1 ").arg(theFilename));
        ui->sSendButton->setEnabled(true);
        ui->sOpenButton->setEnabled(false);
    }
}

void Server::sSendBtn_clicked()
{
    // tcpServer开始监听
    if (!tServer->listen(QHostAddress::Any, tPort)) {
        qDebug() << tServer->errorString();
        close();
        return;
    }
    ui->sStatusLabel->setText("等待对方接收......");
    emit sendFileName(theFilename);  //发送信号
}

void Server::sCloseBtn_clicked()
{
    if(tServer->isListening())
    {
        tServer->close();
        if (localFile->isOpen())
            localFile->close();
        tcpSocket->abort();
    }
    close();
}

void Server::refused()
{
    tServer->close();
    ui->sStatusLabel->setText(tr("对方拒绝接收！"));
}

void Server::closeEvent(QCloseEvent *)
{
    sCloseBtn_clicked();
}

Server::~Server()
{
    delete ui;
}
