#ifndef SERVER_H
#define SERVER_H
//这个类是文件传输的服务端,也是文件传输的界面类
//文件传输采用TCP通信，但不是使用统一的服务端，而是要传输文件的时候才创建一个服务端，接收文件一方就是客户端。
#include <QDialog>
#include <QTcpServer>
#include <QFile>
#include <QElapsedTimer>
#include <QTcpSocket>
namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget* parent = nullptr);
    ~Server();
    void initSrv(); // 初始化服务器
    void refused(); // 关闭服务器
protected:
    void closeEvent(QCloseEvent*);

private:
    Ui::Server* ui;
    qint16 tPort;
    QTcpServer* tServer;
    QString filename;
    QString theFilename;
    QFile* localFile; // 待发送的文件
    qint64 totalBytes; // 总字节数
    qint64 bytesWriten; // 已发送的字节数
    qint64 bytesTobeWrite; // 待发送的字节数
    qint64 payloadSize;
    QByteArray outBlock; // 发送缓冲
    QTcpSocket* tcpSocket;
    QElapsedTimer time;
private slots:
    void sndMsg(); // 发送数据
    void updClntProgress(qint64 numBytes); // 跟新进度条
    void sOpenBtn_clicked();
    void sSendBtn_clicked();
    void sCloseBtn_clicked();

signals:
    void sendFileName(QString filename);
};

#endif // SERVER_H
