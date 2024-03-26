#include "widget.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

//qt6中的多媒体类发生重要变化
//QMediaCaptureSession 是管理本地设备媒体捕获的中心类。
//QMediaCaptureSession类的setVideoOutput和setVideoSink方法之间的冲突问题


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);
    // 布局
    m_openCameraButton = new QPushButton(this);
    m_openCameraButton->setText("打开摄像头");
    m_videoWidget = new QVideoWidget(this);
    m_videoLabel1 = new QLabel(this);
    m_videoLabel1->setFixedSize(400, 300);
    m_videoLabel2 = new QLabel(this);
    m_videoLabel2->setFixedSize(400, 300);
    QVBoxLayout* mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(m_openCameraButton);
    mainlayout->addWidget(m_videoWidget);
    QHBoxLayout* bottomLayout = new QHBoxLayout(this);
    bottomLayout->addWidget(m_videoLabel1);
    bottomLayout->addWidget(m_videoLabel2);
    mainlayout->addLayout(bottomLayout);
    m_videoWidget->setStyleSheet("border:2px solid #333333");
    m_videoLabel1->setStyleSheet("border:2px solid #a04500");
    m_videoLabel2->setStyleSheet("border:2px solid #1144bb");
    // 创建多媒体控件
    m_camera = new QCamera(this);
    m_imageCapture = new QImageCapture(this);
    m_videoSink = new QVideoSink(this);
//    m_camera->set
    m_mediaSession = new QMediaCaptureSession(this);
    m_mediaSession->setCamera(m_camera); // 设置摄像头
//    m_mediaSession->setVideoOutput(m_videoWidget); // 设置视频输出到哪里
    m_mediaSession->setImageCapture(m_imageCapture); // 设置视频捕获对象,这个捕获对象可以获取一个帧
    //QVideoSink类用于访问视频的单个帧 ,设置之后普通的setVideo的方法录制视频将会失效
    m_mediaSession->setVideoSink(m_videoSink);
    // 连接槽函数
    connect(m_openCameraButton, &QPushButton::clicked, this, &Widget::on_openCameraButton_clickded);
    connect(m_imageCapture, &QImageCapture::imageCaptured, this, &Widget::on_imageCaptured);
    connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &Widget::on_videoFrameChanged);
}

void Widget::on_openCameraButton_clickded()
{
    qDebug() << "打开摄像头";
    m_camera->start();
    // QImageCapture::capture()函数的作用是触发一个异步操作来捕获当前摄像头视图中的图像，并将其作为 QImage 对象提供。
    // 这个操作是异步的，意味着函数会立即返回，而图像的捕获和处理将在后台进行。
    // 函数返回值是一个整数值，称为捕获 ID，这个 ID 可以用于跟踪与这次捕获操作相关的事件。
    m_imageCapture->capture();
}

void Widget::on_imageCaptured(int id, const QImage& preview)
{
    m_videoLabel1->setPixmap(QPixmap::fromImage(preview.scaled(m_videoLabel1->size())));
}

void Widget::on_videoFrameChanged()
{
    QVideoFrame frame = m_videoSink->videoFrame();
    frame.map(QVideoFrame::ReadOnly);     //要访问帧的数据，需要先映射到内存
    if (frame.isValid() && frame.isReadable()) {
        QImage videoImg = frame.toImage();
        m_videoLabel2->setPixmap(QPixmap::fromImage(videoImg.scaled(m_videoLabel2->size())));
    }
}




Widget::~Widget()
{
}

