#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "server.h"
//这个类主要创建界面

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    TcpServer(QWidget* parent = nullptr);
    ~TcpServer();

private:
    QListWidget* contentListWidget;
    QLabel* portLabel;
    QLineEdit* portLineEdit;
    QPushButton* createBtn;
    QGridLayout* mainLayout;

private:
    int port;
    Server* server;
public slots:
    void slotCreateServer();
    void updateServer(QString, int);

};
#endif // TCPSERVER_H
