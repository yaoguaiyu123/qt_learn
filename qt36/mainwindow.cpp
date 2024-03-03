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

// 播放音频按钮点击
void MainWindow::on_pushButton_clicked()
{
    QAudioDevice audioDevice = QMediaDevices::defaultAudioOutput(); // 默认音频输出
    if (audioDevice.isNull()) {
        QMessageBox::information(this, "提示", "无音频输入设备");
        return;
    }
    QAudioFormat format = audioDevice.preferredFormat();
    qDebug("sampleRate: %d, channelCount: %d, sampleFormat: %d",
        format.sampleRate(), format.channelCount(), format.sampleFormat());

    QFile file("../36/yinpin.wav");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "文件打开失败";
        return;
    }
    m_mydevice = new MyDevice(file.readAll());

    //必须要指针类型的sink才能播放
    QAudioSink *sink = new QAudioSink(audioDevice, format);
    sink->start(m_mydevice);
}

