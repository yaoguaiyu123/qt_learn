#include "mydevice.h"
#include <QDebug>

MyDevice::MyDevice(QByteArray dataPcm)
    :m_dataPcm(dataPcm)
{
    // 打开
    this->open(QIODevice::ReadOnly);
    m_writeLen = 0;
}


// 读取数据
// 扬声器缺少数据的时候会自动调用这个方法
// 这个方法用于给扬声器提供声音数据
qint64 MyDevice::readData(char* data, qint64 maxlen)
{
    if (m_writeLen >= m_dataPcm.size()) {
        return 0;
    }
    // 计算未播放的数据的长度
    int len = (m_writeLen + maxlen) > m_dataPcm.size() ? (m_dataPcm.size() - m_writeLen) : maxlen;
    // 把要播放的pcm数据存入声卡缓冲区里
    memcpy(data, m_dataPcm.data() + m_writeLen, len);
    m_writeLen += len;
//    qDebug() << "播放:" << m_writeLen;
    return len;

}


qint64 MyDevice::writeData(const char* data, qint64 len){
    Q_UNUSED(data)
    Q_UNUSED(len)
    return 0; // MyDevice 不支持写入
}

int MyDevice::bufferSize()
{
    return m_dataPcm.size();
}


MyDevice::~MyDevice(){
    this->close();
}
