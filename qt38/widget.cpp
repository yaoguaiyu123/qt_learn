#include "widget.h"
#include "./ui_widget.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(audioOutput);
//    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
   // 设置要播放的音频文件的URL
    m_player->setSource(QUrl::fromLocalFile("/run/media/root/study/github_repository/qt_learn/qt38/yinpin.wav"));

   // 播放音频
    m_player->play();
}

