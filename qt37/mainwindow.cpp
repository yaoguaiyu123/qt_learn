#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QVBoxLayout>

//qt中QMediaPlayer是一个高级的视频播放类,而QVideoSink是一个低级的控制视频数据的类
//正如QAudioOutput是一个高级的音频播放类，而QAudioSink是一个低级的控制音频数据的类

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_player = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput;
    m_player->setAudioOutput(audioOutput);
    QVideoWidget* videoWidget = new QVideoWidget(ui->centralwidget);
    videoWidget->resize(600, 400);
    QVBoxLayout* layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(ui->pushButton);
    layout->addWidget(videoWidget);

    m_player->setVideoOutput(videoWidget);
    m_player->setSource(QUrl("../qt37/123.mp4"));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    m_player->play();
}

