// Date:2024/3/27
// Author:妖怪鱼
// Introduction:qt6版本打印所有音频输入设备
#include <QCoreApplication>
#include <QAudioInput>
#include <QMediaDevices>
#include <QDebug>
#include <QAudioDevice>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<QAudioDevice> audioDevices = QMediaDevices::audioInputs();
    for (const QAudioDevice& device : audioDevices) {
        //        QAudioDevice info(input);
        qDebug() << device.description();
    }
    return a.exec();
}
