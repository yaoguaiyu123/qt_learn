#include "widget.h"
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    destinationFile.setFileName("../qt42/yinpin.pcm");
    destinationFile.open(QIODevice::WriteOnly | QIODevice ::Truncate);
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
    audio->start(&destinationFile);
}


void Widget::shandleStateChanged(QAudio::State state)
{
    qDebug() << "状态改变";
}

void Widget::stopRecording()
{
    audio->stop();
    destinationFile.close();
}


Widget::~Widget()
{
}

