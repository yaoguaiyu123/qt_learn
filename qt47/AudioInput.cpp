#include "AudioInput.h"
#include <QAudioFormat>
#include <QDebug>
#include <QThread>

AudioInput::AudioInput(QObject *parent)
        : QThread(parent)
{
        // 设置音频格式
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(8);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::UnSignedInt);

        audio = nullptr;

        //测试
        QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
        foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
            if (deviceInfo.deviceName().contains("input.pci")) {
                info = deviceInfo;
                break;
            }
        }
        if (!info.isFormatSupported(format)) {

            qWarning() << "Audio Input Format Useless!!!!!!!!!!!";
            format = info.nearestFormat(format);
        }


}

AudioInput::~AudioInput()
{
	delete audio;
}

void AudioInput::startCollect()
{
    // 需要把audio的创建放到子线程中
    if (audio == nullptr) {
        qDebug() << "正在初始化";
        audio = new QAudioInput(format, this);
        connect(audio, SIGNAL(stateChanged(QAudio::State)),
            this, SLOT(handleStateChanged(QAudio::State)));
    }
    qDebug() << "初始化完成";
    inputdevice = audio->start();
    connect(inputdevice, &QIODevice::readyRead, this, &AudioInput::onreadyRead);
}

void AudioInput::stopCollect()
{
    disconnect(this, SLOT(onreadyRead()));
    audio->stop();
    inputdevice = nullptr;
}

//接受音频的槽函数
void AudioInput::onreadyRead()
{
    qDebug() << "接收音频的槽函数执行";
}


void AudioInput::handleStateChanged(QAudio::State state)
{
    qDebug() << "AudioInput::handleStateChanged状态改变";
}

