#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioInput>
#include <QFile>
#include <QIODevice>

class MyDevice : public QIODevice {
    Q_OBJECT
public:
    MyDevice(QObject* parent = nullptr);
    ~MyDevice();

private:
    int m_writeLen;
    QByteArray m_dataPcm;
protected:
    qint64 writeData(const char* data, qint64 len);
    qint64 readData(char* data, qint64 maxlen);
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
private slots:
    void shandleStateChanged(QAudio::State state);
    void stopRecording();
    void startRecording();
private:
    QAudioInput* audio;
    //    QFile *destinationFile;
    MyDevice* m_mydevice;
};
#endif // WIDGET_H
