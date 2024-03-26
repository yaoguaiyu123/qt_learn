#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QPushButton>
#include <QLabel>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QVideoSink>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QCamera* m_camera;
    QPushButton* m_openCameraButton;
    QVideoWidget* m_videoWidget;
    QImageCapture* m_imageCapture; // 捕获摄像头的图像的类
    QMediaCaptureSession* m_mediaSession; // 本地媒体捕获中心类
    QLabel *m_videoLabel1, *m_videoLabel2; // 获取捕获到的视频帧
    QVideoSink* m_videoSink;
private slots:
    void on_openCameraButton_clickded();
    void on_imageCaptured(int id, const QImage &preview);
    void on_videoFrameChanged();
};
#endif // WIDGET_H
