#include "widget.h"
#include "ui_widget.h"
#include "linemessage.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_layout = new QVBoxLayout(ui->scrollArea->widget());
    for (int i = 0; i < 20; ++i) {
        LineMessage* lineMsg;
        LineMessageData lineMessageData;
        if (!(i % 2)) {
            lineMessageData = { "今天吃的东西确实是不错的", ":/image/head01.png",1};
            lineMsg = new LineMessage(lineMessageData, MessageUser_Self, this);
        } else {
            lineMessageData = { "确实啊，好久没有吃过这么好吃的东西了", ":/image/head02.png", 1 };
            lineMsg = new LineMessage(lineMessageData, Message_Counterpart, this);
        }
        m_layout->addWidget(lineMsg);
    }
    m_layout->setAlignment(Qt::AlignTop);

//    QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
//    scrollBar->setValue(scrollBar->maximum());

    //需要延时设置滚动条高度
    QTimer::singleShot(10, [=](){
        QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    });

}


Widget::~Widget()
{
    delete ui;
}

// 发送按钮点击
void Widget::on_pushButton_clicked()
{
    QString content = ui->textEdit->toPlainText();
    if (content != "") {
        int lineCount = ui->textEdit->document()->lineCount();
        LineMessageData lineMessageData = {content, ":/image/head01.png" ,lineCount};
        LineMessage* lineMsg = new LineMessage(lineMessageData, MessageUser_Self, this);
        m_layout->addWidget(lineMsg);
        ui->textEdit->clear();
        QTimer::singleShot(10, [=](){
            QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
            scrollBar->setValue(scrollBar->maximum());
        });
    }

}

