// Date:2024/2/3
// Author:妖怪鱼
// Introduction:获取本机网络信息
#include "networkinformation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetWorkInformation w;
    w.show();
    return a.exec();
}
