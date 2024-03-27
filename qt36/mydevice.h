#ifndef MYDEVICE_H
#define MYDEVICE_H

#include <QIODevice>

class MyDevice : public QIODevice
{
    Q_OBJECT
public:
    MyDevice(QByteArray dataPcm);
    ~MyDevice();
    int bufferSize();

protected:
    virtual qint64 readData(char* data, qint64 maxlen);
    virtual qint64 writeData(const char* data, qint64 len);
private:
    int m_writeLen; // 记录已经写入多少字节
    QByteArray m_dataPcm;  //存放pcm数据
};

#endif // MYDEVICE_H
