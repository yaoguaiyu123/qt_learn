#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    widget1 = new QWidget();
    widget2 = new QWidget();
    widget2->hide();
    layout1 = new QGridLayout(widget1);
    nameLabel = new QLabel("姓名:");
    nameLineEdit = new QLineEdit();
    okButton = new QPushButton();
    sexLabel = new QLabel("性别:");
    sexcombobox = new QComboBox();
    sexcombobox->addItem("男");
    sexcombobox->addItem("女");
    okButton = new QPushButton("确定");
    moreButton = new QPushButton("详细");
    connect(moreButton, SIGNAL(clicked(bool)), this, SLOT(changeDialogSize())); // 连接槽函数
    layout1->addWidget(nameLabel, 0, 0);
    layout1->addWidget(nameLineEdit, 0, 1);
    layout1->addWidget(okButton, 0, 2);
    layout1->addWidget(sexLabel, 1, 0);
    layout1->addWidget(sexcombobox, 1, 1);
    layout1->addWidget(moreButton, 1, 2);
    layout2 = new QGridLayout(widget2);
    ageLabel = new QLabel("年龄:");
    ageLineEdit = new QLineEdit();
    departmentLabel = new QLabel("部门:");
    departmentCombobox = new QComboBox();
    departmentCombobox->addItem("部门1");
    departmentCombobox->addItem("部门2");
    departmentCombobox->addItem("部门3");
    departmentCombobox->addItem("部门4");
    emailLabel = new QLabel("邮箱:");
    emailLineEdit = new QLineEdit();
    layout2->addWidget(ageLabel, 0, 0);
    layout2->addWidget(ageLineEdit, 0, 1, 1, 2);
    layout2->addWidget(departmentLabel, 1, 0);
    layout2->addWidget(departmentCombobox, 1, 1, 1, 2);
    layout2->addWidget(emailLabel, 2, 0);
    layout2->addWidget(emailLineEdit, 2, 1, 1, 2);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize); // 对话框尺寸保持相对固定,始终保持各个控件的默认尺寸,不能使用拖拽改变空间大小
    mainLayout->addWidget(widget1);
    mainLayout->addWidget(widget2);
}

Dialog::~Dialog()
{
}

void Dialog::changeDialogSize(){
    if(widget2->isHidden()){
        widget2->show();
        moreButton->setText("收起");
    }else{
        widget2->hide();
        moreButton->setText("详情");
    }
}
