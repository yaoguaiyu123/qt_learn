#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTextBlock>
#include <QPainterPath>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::topWidget)
    , m_textEdit(new QTextEdit(this))
    , m_document(m_textEdit->document())
{
    ui->setupUi(this);
    resize(640, 480);
    setCentralWidget(m_textEdit);
    m_textEdit->append("Hello world001");

    QTextCursor cursor = m_textEdit->textCursor();
    //1.直接使用路径插入
    // cursor.insertImage(":/image/head01.png");

    //2.使用QTextImageFormat插入
    // 好处是可以设置大小，图片的大小是保持宽高比变化的，一般来说只要width和height设置一个就行了
    QTextImageFormat imageFormat;
    imageFormat.setWidth(120);
    imageFormat.setName(":/image/head02.png");
    // cursor.insertImage(imageFormat);
    m_textEdit->append("Hello world002");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 获得content
void MainWindow::on_actioncontent_triggered()
{
    QTextBlock block = m_document->begin();  // 获取文档的第一个块

    while (block.isValid()) {
        QTextBlock::iterator it;
        // 遍历块中的所有元素
        for (it = block.begin(); !(it.atEnd()); ++it) {
            QTextFragment fragment = it.fragment();
            if (fragment.isValid()) {
                if (fragment.charFormat().isImageFormat()) {
                    // 处理图片
                    QTextImageFormat imgFormat = fragment.charFormat().toImageFormat();
                    QString imgName = imgFormat.name();  // 图片名称
                    qDebug() << "Image found:" << imgName;
                } else {
                    // 处理文本
                    QString text = fragment.text();  // 块中的文本内容
                    qDebug() << "Text:" << text;
                }
            }
        }
        block = block.next();  // 移动到下一个块
    }
}


