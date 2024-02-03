#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QHostInfo>
#include <QNetworkInterface>

class NetWorkInformation : public QWidget
{
    Q_OBJECT

public:
    NetWorkInformation(QWidget* parent = nullptr);
    ~NetWorkInformation();
    void gethostinformation();
public slots:
    void showDetail();
private:
    QLabel *hostLabel, *ipLabel;
    QLineEdit *lineEditLocalhostname, *lineEditAddress;
    QPushButton* detailButton;
    QGridLayout* mainLayout;

};
#endif // NETWORKINFORMATION_H
