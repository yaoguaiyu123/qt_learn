#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QTimer>

class UDPServer : public QDialog
{
    Q_OBJECT

public:
    UDPServer(QWidget* parent = nullptr);
    ~UDPServer();

public slots:
    void startBtnClicked();
    void timeout();

private:
    QLabel* timerLabel;
    QLineEdit* textLineEdit;
    QPushButton* startBtn;
    QVBoxLayout* mainLayout;

private:
    int port;     //服务器的端口号
    bool isStarted;
    QUdpSocket* udpSocket;
    QTimer* timer;
};
#endif // UDPSERVER_H
