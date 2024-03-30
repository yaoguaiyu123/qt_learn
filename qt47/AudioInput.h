#pragma once

//音频输入类，兼顾音频数据的发送
//接收麦克风的输入
#include <QObject>
#include <QAudioInput>
#include <QIODevice>
#include <QWidget>
#include <QThread>
class AudioInput : public QThread
{
	Q_OBJECT
private:
        QAudioInput *audio;
        QIODevice* inputdevice;
        QAudioFormat format;
public:
        AudioInput(QObject *par = 0);
	~AudioInput();
private slots:
	void onreadyRead();
	void handleStateChanged(QAudio::State);
public slots:
	void startCollect();
	void stopCollect();
signals:
	void audioinputerror(QString);
};
