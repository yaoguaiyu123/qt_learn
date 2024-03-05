// Date:2024/3/2
// Author:妖怪鱼
// Introduction:第一个Qt Quick案例
#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QQmlApplicationEngine对象用于加载qml文件
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("qml01", "Main");

    return app.exec();
}
