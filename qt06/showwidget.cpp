#include "showwidget.h"
#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent)
    : QWidget{parent}
{
    imageLabel = new QLabel();
    imageLabel->setScaledContents(true);
    text = new QTextEdit();
    QHBoxLayout* mainLayout = new QHBoxLayout(this);   //让label中的图像保持长宽比例缩放
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(text);
}
