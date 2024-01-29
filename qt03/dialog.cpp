#include "dialog.h"
#include "ui_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    createLeftFrame();
    createRightFrame();
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(leftFrame);
    mainLayout->addWidget(rightFrame);
}

void Dialog::createLeftFrame()
{
    leftFrame = new QFrame();
    windowLabel = new QLabel("Window");
    windowcombobox = new QComboBox();
    fillColorList(windowcombobox);  //初始化下拉框的选项
    connect(windowcombobox, SIGNAL(activated(int)), this, SLOT(showWindow())); // 连接槽函数
    windowTextLabel = new QLabel("WindowText");
    windowTextCombobox = new QComboBox();
    fillColorList(windowTextCombobox);
    connect(windowTextCombobox, SIGNAL(activated(int)), this, SLOT(showWindowText()));
    buttonLabel = new QLabel("Button");
    buttonCombobox = new QComboBox();
    fillColorList(buttonCombobox);
    connect(buttonCombobox, SIGNAL(activated(int)), this, SLOT(showButton()));
    buttonTextLabel = new QLabel("ButtonText");
    buttonTextCombobox = new QComboBox();
    fillColorList(buttonTextCombobox);
    connect(buttonTextCombobox, SIGNAL(activated(int)), this, SLOT(showButtonText()));
    baseLabel = new QLabel("Base");
    baseCombobox = new QComboBox();
    fillColorList(baseCombobox);
    connect(baseCombobox, SIGNAL(activated(int)), this, SLOT(showBase()));
    QGridLayout* mainLayout = new QGridLayout(leftFrame);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowcombobox, 0, 1);
    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextCombobox, 1, 1);
    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonCombobox, 2, 1);
    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextCombobox, 3, 1);
    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseCombobox, 4, 1);
}

void Dialog::createRightFrame()
{
    rightFrame = new QFrame();
    label1 = new QLabel("请选择一个值:");
    combobox = new QComboBox();
    label2 = new QLabel("请输入字符串:");
    lineEdit = new QLineEdit();
    textEdit = new QTextEdit();
    QGridLayout* topLayout = new QGridLayout();
    topLayout->addWidget(label1, 0, 0);
    topLayout->addWidget(combobox, 0, 1);
    topLayout->addWidget(label2, 1, 0);
    topLayout->addWidget(lineEdit, 1, 1);
    topLayout->addWidget(textEdit, 2, 0, 1, 2);
    okButton = new QPushButton("确认");
    cancelButton = new QPushButton("取消");
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);
    QVBoxLayout* mainLayout = new QVBoxLayout(rightFrame);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
}

void Dialog::showWindow()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowcombobox->currentIndex()]); // 获得当前所选的颜色值
    QPalette p = rightFrame->palette(); // 获取rightFrame的内置画板
    p.setColor(QPalette::Window, color); // 设置颜色
    rightFrame->setPalette(p);
    rightFrame->update();
}

void Dialog::showWindowText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowTextCombobox->currentIndex()]);
    QPalette p = rightFrame->palette();
    p.setColor(QPalette::WindowText, color);
    rightFrame->setPalette(p);
    rightFrame->update();
}

void Dialog::showButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonCombobox->currentIndex()]);
    QPalette p = rightFrame->palette();
    p.setColor(QPalette::Button, color);
    rightFrame->setPalette(p);
    rightFrame->update();
}

void Dialog::showButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextCombobox->currentIndex()]);
    QPalette p = rightFrame->palette();
    p.setColor(QPalette::ButtonText, color);
    rightFrame->setPalette(p);
    rightFrame->update();
}

void Dialog::showBase()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseCombobox->currentIndex()]);
    QPalette p = rightFrame->palette();
    p.setColor(QPalette::Base, color);
    rightFrame->setPalette(p);
    rightFrame->update();
}


void Dialog::fillColorList(QComboBox* combobox)
{
    QStringList colorList = QColor::colorNames();
    QString color;
    foreach (color, colorList) {
        QPixmap pix(QSize(70, 20));    //创建一个图像
        pix.fill((QColor(color)));    //给图像填充颜色
        combobox->addItem(QIcon(pix),NULL);   //添加一个新项，包含图标和NULL文本
        combobox->setIconSize(QSize(70,20));  //设置combobox中的图标大小
        combobox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }

}

Dialog::~Dialog()
{
    delete ui;
}

