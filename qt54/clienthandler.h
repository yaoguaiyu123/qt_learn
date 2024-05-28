#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QRunnable>
#include <QTcpSocket>

class ClientHandler : public QRunnable
{
public:
    ClientHandler(qintptr socketDescriptor);
    void run() override;
    QString getRandomString(int nLen);
private:
    qintptr socketDescriptor;
    bool is_success = false;
    bool is_begin = false;

};

#endif // CLIENTHANDLER_H
