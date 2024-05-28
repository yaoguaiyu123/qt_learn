#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QThreadPool>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);
    ~Server();
    bool startServer(const QHostAddress &address, quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
};

#endif // SERVER_H
