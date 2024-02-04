#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QUdpSocket>

class UDPClient : public QDialog
{
    Q_OBJECT

public:
    UDPClient(QWidget* parent = nullptr);
    ~UDPClient();
public slots:
    void closeBtnClicked();
    void dataReceived();

private:
    int port;
    QUdpSocket* udpSocket;
private:
    QTextEdit* receiveTextEdit;
    QPushButton* closeBtn;
    QVBoxLayout* mainLayout;
};
#endif // UDPCLIENT_H
