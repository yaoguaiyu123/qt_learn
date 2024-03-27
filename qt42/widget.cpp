#include "widget.h"
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

MyDevice::MyDevice(QObject* parent)
    : QIODevice(parent)
{
    m_writeLen = 0;
    m_dataPcm.resize(1024 * 1024 * 4); // 4mb的最大容量
}

qint64 MyDevice::writeData(const char* data, qint64 len)
{
    if (m_writeLen >= m_dataPcm.size()) {
        return 0;
    }
    int writelen = (m_writeLen + len) > m_dataPcm.size() ? (m_dataPcm.size() - m_writeLen) : len;
    memcpy(m_dataPcm.data() + m_writeLen, data, writelen);
    m_writeLen += writelen;
    return writelen;
}

qint64 MyDevice::readData(char* data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)
    return 0;
}

MyDevice::~MyDevice()
{
    // 在析构函数中将内存中的数据持久化保存
    m_dataPcm.resize(m_writeLen);    //重新变化缓存大小,避免冗余
    QFile file("../qt42/yinpin.pcm");
    file.open(QIODevice::WriteOnly | QIODevice ::Truncate);
    file.write(m_dataPcm);
    file.close();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //    destinationFile.setFileName("../qt42/yinpin.pcm");
    //    destinationFile.open(QIODevice::WriteOnly | QIODevice ::Truncate);
    m_mydevice = new MyDevice(this);

    QPushButton* button1 = new QPushButton(this);
    QPushButton* button2 = new QPushButton(this);
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    // 选择正确的设备
    QAudioDeviceInfo info;
    foreach (const QAudioDeviceInfo& deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        if (deviceInfo.deviceName().contains("alsa_input.pci-0000_06_00.6.analog-stereo")) {
            info = deviceInfo;
            break;
        }
    }

    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }

    audio = new QAudioInput(info, format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(shandleStateChanged(QAudio::State)));

    //    QTimer::singleShot(3000, this, SLOT(stopRecording())); // 计时3s

    button1->setText("开始录音");
    button2->setText("停止录音");
    QHBoxLayout* mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(button1);
    mainlayout->addWidget(button2);
    connect(button1, &QPushButton::clicked, this, &Widget::startRecording);
    connect(button2, &QPushButton::clicked, this, &Widget::stopRecording);
    resize(400,200);
}
void Widget::startRecording(){
    m_mydevice->open(QIODevice::WriteOnly);
    audio->start(m_mydevice);
}


void Widget::shandleStateChanged(QAudio::State state)
{
    qDebug() << "状态改变";
}

void Widget::stopRecording()
{
    audio->stop();
    m_mydevice->close();
}


Widget::~Widget()
{
}

