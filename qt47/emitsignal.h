#ifndef EMITSIGNAL_H
#define EMITSIGNAL_H

#include <QThread>

class EmitSIgnal : public QThread
{
    Q_OBJECT
public:
    EmitSIgnal(QObject* parent);

protected:
    void run();
signals:

    void signal0();
    void signal1();
};

#endif // EMITSIGNAL_H
