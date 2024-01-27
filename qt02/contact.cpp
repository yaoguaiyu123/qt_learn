#include "contact.h"

Contact::Contact(QWidget* parent)
    : QWidget(parent)
{
    emailLabel = new QLabel("电子邮箱:");
    emailEdit = new QLineEdit();
    addressLabel = new QLabel("联系地址:");
    addressEdit = new QLineEdit();
    codeLabel = new QLabel("邮政编码:");
    codeEdit = new QLineEdit();
    movtelLabel = new QLabel("移动电话:");
    movtelEdit = new QLineEdit();
    movtelCheckBox = new QCheckBox();
    protalLabel = new QLabel("固定电话:");
    protelEdit = new QLineEdit();
    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(emailLabel, 0, 0);
    mainLayout->addWidget(emailEdit, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0);
    mainLayout->addWidget(addressEdit, 1, 1);
    mainLayout->addWidget(codeLabel, 2, 0);
    mainLayout->addWidget(codeEdit, 2, 1);
    mainLayout->addWidget(movtelLabel, 3, 0);
    mainLayout->addWidget(movtelEdit, 3, 1);
    mainLayout->addWidget(movtelCheckBox, 3, 2);
    mainLayout->addWidget(protalLabel, 4, 0);
    mainLayout->addWidget(protelEdit, 4, 1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);   //固定大小
}

Contact::~Contact(){

}
