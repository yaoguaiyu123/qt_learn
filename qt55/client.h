#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QFile>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    bool connectToServer(const QString &host, quint16 port);
    void uploadFile(const QString& filePath);
    void handleBytesWritten(qint64 size);
    // void downloadFile(const QString &fileName, const QString &savePath);
    ~Client();
private slots:
    // void onReadyRead();
signals:
private:
    QTcpSocket socket;
    QFile file;
    qint64 haveWritten;
    qint64 toWrite;
};

#endif // CLIENT_H
