#include "baseinfo.h"

Baseinfo::Baseinfo(QWidget* parent)
    : QWidget(parent)
{
    // 左侧的布局
    userNameLabel = new QLabel("用户名:");
    usernameEdit = new QLineEdit();
    nameLabel = new QLabel("姓名:");
    nameEdit = new QLineEdit();
    sexLabel = new QLabel("性别:");
    sexEdit = new QComboBox();
    sexEdit->addItem("男");
    sexEdit->addItem("女");
    departmentLabel = new QLabel("部门:");
    departmentEdit = new QTextEdit();
    ageLabel = new QLabel("年龄:");
    ageEdit = new QLineEdit();
    otherLabel = new QLabel("备注:");
    otherLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    leftLayout = new QGridLayout(); // 创建布局
    leftLayout->addWidget(userNameLabel, 0, 0);
    leftLayout->addWidget(usernameEdit, 0, 1);
    leftLayout->addWidget(nameLabel, 1, 0);
    leftLayout->addWidget(nameEdit, 1, 1);
    leftLayout->addWidget(sexLabel, 2, 0);
    leftLayout->addWidget(sexEdit, 2, 1);
    leftLayout->addWidget(departmentLabel, 3, 0);
    leftLayout->addWidget(departmentEdit, 3, 1);
    leftLayout->addWidget(ageLabel, 4, 0);
    leftLayout->addWidget(ageEdit, 4, 1);
    leftLayout->addWidget(otherLabel, 5, 0, 1, 2);
    leftLayout->setColumnStretch(0, 1); // 将第0列的拉伸因子设置为1
    leftLayout->setColumnStretch(1, 3); // 将第1列的拉伸因子设置为3
    // 右上角的布局
    headLabel = new QLabel("头像:");
    headPicLabel = new QLabel();
    QPixmap icon("../02/tx.png");
    headPicLabel->setPixmap(icon); // 创建一个图片
    headPicLabel->resize(icon.width(), icon.height());
    updateHeadButton = new QPushButton("更新头像");
    rightTopLayout = new QHBoxLayout();
    rightTopLayout->setSpacing(20);
    rightTopLayout->addWidget(headLabel);
    rightTopLayout->addWidget(headPicLabel);
    rightTopLayout->addWidget(updateHeadButton);
    // 右下角的布局
    introductionLabel = new QLabel("个人介绍");
    introductionTextEdit = new QTextEdit();
    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(10, 10, 10, 10);
    rightLayout->addLayout(rightTopLayout);
    rightLayout->addWidget(introductionLabel);
    rightLayout->addWidget(introductionTextEdit);

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);   //将布局大小固定
}

Baseinfo::~Baseinfo()
{
}
