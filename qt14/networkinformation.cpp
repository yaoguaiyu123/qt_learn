#include "networkinformation.h"

NetWorkInformation::NetWorkInformation(QWidget *parent)
    : QWidget(parent)
{
    hostLabel = new QLabel("主机名:");
    lineEditLocalhostname = new QLineEdit();
    ipLabel = new QLabel("IP地址:");
    lineEditAddress = new QLineEdit();
    detailButton = new QPushButton("详细");
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(lineEditLocalhostname, 0, 1);
    mainLayout->addWidget(ipLabel, 1, 0);
    mainLayout->addWidget(lineEditAddress, 1, 1);
    mainLayout->addWidget(detailButton, 2, 0, 1, 2);
    resize(300, 200);
    gethostinformation();
    connect(detailButton, SIGNAL(clicked(bool)), this, SLOT(showDetail()));
}

void NetWorkInformation::showDetail()
{
    QString detail = "";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); // 得到所有网络接口
    for (int i = 0; i < list.count(); ++i) {
        QNetworkInterface interface = list.at(i);
        detail = detail + "设备:" + interface.name() + "\n";
        detail = detail + "硬件地址:" + interface.hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> entryList = interface.addressEntries(); // 得到每个接口的所有地址条目
        qDebug() << "地址条目数量:" << entryList.count();
        for (int j = 0; j < entryList.count(); ++j) {
            QNetworkAddressEntry entry = entryList.at(j);
            //QNetworkAddressEntry类表示网络接口的一个地址条目，其中包含了 IP 地址、子网掩码、广播地址和有效期等信息。
            detail = detail + "\t" + "IP地址:" + entry.ip().toString() + "\n";
            detail = detail + "\t" + "子网掩码:" + entry.netmask().toString() + "\n";
            detail = detail + "\t" + "广播地址:" + entry.broadcast().toString() + "\n";
        }
    }
    QMessageBox::information(this, "详细信息:", detail);
}

void NetWorkInformation::gethostinformation()
{
    QString localHostName = QHostInfo::localHostName(); // 获取本地主机名
    lineEditLocalhostname->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName); // 根据主机名获取相关主机信息
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if (!listAddress.empty()) {
        qDebug() << "listAddress.count():" <<listAddress.count();
        lineEditAddress->setText(listAddress.at(1).toString());
    }
}

NetWorkInformation::~NetWorkInformation()
{
}

