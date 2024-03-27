#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioInput>
#include <QFile>

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
    QFile destinationFile;
};
#endif // WIDGET_H
