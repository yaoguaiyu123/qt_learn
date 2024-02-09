#ifndef CLIENT_H
#define CLIENT_H

//文件传输的客户端
#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QElapsedTimer>
class QTcpSocket;

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
~Client();

    void setHostAddr(QHostAddress addr);
    void setFileName(QString name);

protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::Client *ui;

    QTcpSocket *tClnt;
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;

    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    QString fileName;
    QFile *locFile;
    QByteArray inBlock;

    QElapsedTimer time;

private slots:

    void newConn();
    void readMsg();
    void displayErr(QAbstractSocket::SocketError);
    void cCancleBtn_clicked();
    void cCloseBtn_clicked();
};

#endif // CLIENT_H
