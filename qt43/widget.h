#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QIODevice>

QT_BEGIN_NAMESPACE
    namespace Ui { class Widget; }
QT_END_NAMESPACE

    class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QAudioInput* m_audioInput;
    QIODevice* m_ioDevice;
private slots:
    void shandleStateChanged(QAudio::State state);
    void onReadyRead();
    void on_startBtn_clicked();
    void on_endBtn_clicked();
    };
#endif // WIDGET_H
