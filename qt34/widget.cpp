#include "widget.h"
#include "ui_widget.h"
#include "linemessage.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QScrollBar>

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
            lineMessageData = { "今天吃的东西确实是不错的", ":/image/head01.png" };
            lineMsg = new LineMessage(lineMessageData, MessageUser_Self, this);
        } else {
            lineMessageData = { "确实啊，好久没有吃过这么好吃的东西了", ":/image/head02.png" };
            lineMsg = new LineMessage(lineMessageData, Message_Counterpart, this);
        }
        m_layout->addWidget(lineMsg);
    }
    m_layout->setAlignment(Qt::AlignTop);
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
        LineMessageData lineMessageData = {content, ":/image/head01.png" };
        LineMessage* lineMsg = new LineMessage(lineMessageData, MessageUser_Self, this);
        m_layout->addWidget(lineMsg);
        ui->textEdit->clear();
        QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();  //得到滚动条
        scrollBar->setValue(scrollBar->maximumHeight());
    }

}

