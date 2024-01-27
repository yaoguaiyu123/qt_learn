#include "detail.h"

Detail::Detail(QWidget* parent)
    : QWidget(parent)
{
    nationLabel = new QLabel("国家/地区:");
    nationEdit = new QComboBox();
    nationEdit->addItem("中国");
    nationEdit->addItem("日本");
    nationEdit->addItem("韩国");
    nationEdit->addItem("美国");
    provinceLabel = new QLabel("省份:");
    provinceEdit = new QComboBox();
    provinceEdit->addItem("浙江");
    provinceEdit->addItem("重庆");
    provinceEdit->addItem("四川");
    provinceEdit->addItem("贵州");
    provinceEdit->addItem("陕西");
    cityLabel = new QLabel("城市:");
    cityEdit = new QLineEdit();
    introductLabel = new QLabel("个人说明:");
    introductionEdit = new QTextEdit();
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nationLabel,0,0);
    mainLayout->addWidget(nationEdit,0,1);
    mainLayout->addWidget(provinceLabel,1,0);
    mainLayout->addWidget(provinceEdit,1,1);
    mainLayout->addWidget(cityLabel,2,0);
    mainLayout->addWidget(cityEdit,2,1);
    mainLayout->addWidget(introductLabel,3,0);
    mainLayout->addWidget(introductionEdit,3,1);
}

Detail::~Detail(){

}
