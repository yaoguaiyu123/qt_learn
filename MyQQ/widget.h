#ifndef WIDGET_H
#define WIDGET_H
//这个类显示聊天界面
//这里实现消息传输使用的是UDP，之后重构项目的话改成TCP
//UdpSocket在此创建
#include <QWidget>
#include <QUdpSocket>
#include "server.h"
#include "client.h"
class QTcpSocket;
enum MsgType { Msg,
    UsrEnter,
    UsrLeft,
    FileName,
    Refuse };
//枚举表示聊天信息，用户加入，用户退出，文件名，拒绝接受文件

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr,QString username = "");
    ~Widget();

protected:
    void userEnter(QString username, QString ipaddr); // 处理新用户加入
    void userLeft(QString username, QString time); // 处理用户离开
    void sendMsg(MsgType type, QString srvaddr = ""); // 广播消息
    QString getIp(); // 获取IP地址
    QString getUsername(); // 获取用户名
    QString getMessage();   //获取聊天消息
    void hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename);


private:
    Ui::Widget *ui;
    QUdpSocket* udpSocket;
    qint64 port;
    QString username;
    QString filename;
    Server* srv;   //文件传输服务端
private slots:
    void sendBtn_clicked();
    void processPendingDatagrams();
    void getFileName(QString);
    void sendTBtn_clicked();
};

#endif // WIDGET_H
