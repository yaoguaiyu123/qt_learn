#include "widget.h"
#include "ui_widget.h"
#include <QAudioFormat>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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

    m_audioInput = new QAudioInput(info, format, this);
    connect(m_audioInput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(shandleStateChanged(QAudio::State)));
}

void Widget::shandleStateChanged(QAudio::State state)
{
    qDebug() << "状态改变";
}


Widget::~Widget()
{
    delete ui;
}


void Widget::on_startBtn_clicked()
{
    m_ioDevice = m_audioInput->start();
    connect(m_ioDevice, &QIODevice::readyRead, this, &Widget::onReadyRead);
}


void Widget::onReadyRead()
{
    qDebug() << "接收到信息";
}

void Widget::on_endBtn_clicked()
{
    m_ioDevice = nullptr;
    disconnect(m_ioDevice, &QIODevice::readyRead, this, &Widget::onReadyRead);   //解除槽函数连接
}







