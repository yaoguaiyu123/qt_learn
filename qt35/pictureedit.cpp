#include "pictureedit.h"
#include "ui_pictureedit.h"

PictureEdit::PictureEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PictureEdit)
{
    ui->setupUi(this);

    // 加载函数
    loadImage();

    // 显示头像裁剪活动和窗口
    m_psDialog = new PhotoShotDialog(ui->label);
    m_psDialog->show();
}

PictureEdit::~PictureEdit()
{
    delete ui;
}


void PictureEdit::loadImage()
{
    m_pixmap.load("../35/head.png");
    m_pixmap = m_pixmap.scaled(ui->label->width(),ui->label->height());   //pixmap使用scaled可以缩放图片
    ui->label->setPixmap(m_pixmap);
}

// 截图按钮点击
void PictureEdit::on_pushButton_clicked()
{
    QPixmap pixmap = m_pixmap.copy(m_psDialog->getCurrentCutRect());
    pixmap.save("../35/cut.png", "png");

}

