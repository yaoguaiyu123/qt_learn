// Date:2024/3/25
// Author:妖怪鱼
// Introduction:获取网络的程序
#include "widget.h"

#include <QApplication>

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>
#include <QDebug>

void fetchWebPage(const QUrl &url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        QByteArray data = reply->readAll();
        QString html = QTextCodec::codecForName("UTF-8")->toUnicode(data);
        qDebug() << html;
        reply->deleteLater();
        reply->manager()->deleteLater();
    });
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUrl url("https://www.baidu.com/");
    fetchWebPage(url);

    return a.exec();
}
