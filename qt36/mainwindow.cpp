#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QAudioSource>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Qt6音频播放步骤
//1.创建一个一个QAudioDevice对象
//2.创建一个QAudioFormat对象,通过调用QAudioDevice对象的defaultAudioOutput方法给其初始化
//3.创建一个QFile对象,打开音频文件
//4.创建一个MyDevice对象,其中MyDevice是一个自定义的类，继承自QIoDevice类,需要实现readData和writeData两个函数
// 构造函数中会将QFile文件中的数据都初始化到其m_data中
//5.创建一个QAudioSink对象(堆对象)，构造函数中传入audioDevice:QAudioDevice 和 format:QAudioFormat两个参数
//6.调用sink:QAudioSink的start函数,传入MyDevice对象作为参数

// 播放音频按钮点击
void MainWindow::on_pushButton_clicked()
{
    QAudioDevice audioDevice = QMediaDevices::defaultAudioOutput(); // 默认音频输出
    if (audioDevice.isNull()) {
        QMessageBox::information(this, "提示", "无音频输入设备");
        return;
    }
    QAudioFormat format = audioDevice.preferredFormat();
//    sampleRate 表示采样率，即每秒钟采集的样本数。
//    channelCount 表示声道数，即音频通道的数量。
//    sampleFormat 表示采样格式，可能是整数值，用于表示不同的采样位深度和编码方式。

    qDebug("sampleRate: %d, channelCount: %d, sampleFormat: %d",
        format.sampleRate(), format.channelCount(), format.sampleFormat());
    format.setSampleRate(8000);

    QFile file("../qt42/yinpin.pcm");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "文件打开失败";
        return;
    }
    m_mydevice = new MyDevice(file.readAll());
    qDebug() << "m_mydevice->bufferSize():" << m_mydevice->bufferSize();

    //必须要指针类型的sink才能播放
    QAudioSink *sink = new QAudioSink(audioDevice, format);
    sink->start(m_mydevice);
}

