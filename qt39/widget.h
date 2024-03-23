#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIODevice>
#include <QAudioFormat>
#include <QMediaDevices>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QAudioSink>
#include <QTimer>
class Generator;

//界面类
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void initializeWindow();
    void initializeAudio(const QAudioDevice &deviceInfo);
private slots:
    void toggleMode();
    void toggleSuspendResume();
    void deviceChanged(int index);
    void volumeChanged(int);
    void updateAudioDevices();
private:
    QMediaDevices *m_devices = nullptr;
    QTimer *m_pushTimer = nullptr;

           // Owned by layout
    QPushButton *m_modeButton = nullptr;
    QPushButton *m_suspendResumeButton = nullptr;
    QComboBox *m_deviceBox = nullptr;
    QLabel *m_volumeLabel = nullptr;
    QSlider *m_volumeSlider = nullptr;     //滑动条控件

    QScopedPointer<Generator> m_generator;     //QScopedPointer是qt的智能指针
    QScopedPointer<QAudioSink> m_audioOutput;

    bool m_pullMode = true;
};

// 生成一段音频的类，继承自QIODevice
class Generator : public QIODevice {
    Q_OBJECT
public:
    Generator(const QAudioFormat& format, qint64 durationUs, int sampleRate);
    void start();
    void stop();

    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;
    qint64 bytesAvailable() const override;
    qint64 size() const override { return m_buffer.size(); }
private:
    qint64 m_pos = 0;
    QByteArray m_buffer;
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

};

#endif // WIDGET_H





