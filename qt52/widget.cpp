#include "widget.h"
#include "./ui_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QFileInfo>

bool isImageFile(const QFileInfo &fileInfo) {
    // 检查文件扩展名
    return fileInfo.suffix().compare("png", Qt::CaseInsensitive) == 0 ||
        fileInfo.suffix().compare("jpg", Qt::CaseInsensitive) == 0 ||
        fileInfo.suffix().compare("jpeg", Qt::CaseInsensitive) == 0 ||
        fileInfo.suffix().compare("bmp", Qt::CaseInsensitive) == 0 ||
        fileInfo.suffix().compare("gif", Qt::CaseInsensitive) == 0;
}

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::topWidget)
{
    ui->setupUi(this);
    QVBoxLayout layout(this);

    QLabel* imageLabel = new QLabel;
    layout.addWidget(imageLabel);

    // 获取剪切板的内容
    QClipboard* clipboard = QGuiApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();
    if (mimeData->hasImage()) {
        // 将图片数据转为QImage
        QImage img = qvariant_cast<QImage>(mimeData->imageData());
        if (!img.isNull()) {
            ui->label->setPixmap(QPixmap::fromImage(img));
        }
    } else if (mimeData->hasUrls()) {
        // 处理文件路径
        QList<QUrl> urls = mimeData->urls();
        if (!urls.isEmpty() && urls.first().isLocalFile()) {
            QString filePath = urls.first().toLocalFile();
            QFileInfo fileInfo(filePath);
            if (fileInfo.exists() && isImageFile(fileInfo)) {
                QImage img(filePath);
                if (!img.isNull()) {
                    ui->label->setPixmap(QPixmap::fromImage(img));
                }
            } else {
                qDebug() << "剪切板中的文件是别的文件";
            }
        } else if (mimeData->hasText()) {
            qDebug() << "剪切板内容：" << mimeData->text();
        } else {
            qDebug() << "剪切板中没有图片或文本";
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
