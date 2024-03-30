// Date:2024/3/27
// Author:妖怪鱼
// Introduction:qt5版本打印所有音频输入设备
#include <QCoreApplication>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    foreach (const QAudioDeviceInfo& deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        qDebug() << deviceInfo.deviceName();
    }
    return a.exec();
}
