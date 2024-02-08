#ifndef SERVER_H
#define SERVER_H
//这个类是文件传输的服务端,也是文件传输的界面类
//文件传输采用TCP通信，但不是使用统一的服务端，而是要传输文件的时候才创建一个服务端，接收文件一方就是客户端。
#include <QDialog>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

        public:
                 explicit Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
