#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QRunnable>
class Client;


class ClientThread : public QRunnable {
    // Q_OBJECT
public:
    ClientThread();
    ~ClientThread();

protected:
    void run() override;
private:
};

#endif // CLIENTTHREAD_H
