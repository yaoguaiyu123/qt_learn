#ifndef WATCHER_H
#define WATCHER_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemWatcher>

QT_BEGIN_NAMESPACE
    namespace Ui { class Watcher; }
QT_END_NAMESPACE

    class Watcher : public QWidget
{
    Q_OBJECT

public:
    Watcher(QWidget* parent = nullptr);
    ~Watcher();
public slots:
    void directoryChanged(QString path);
private:
    Ui::Watcher *ui;
    QLabel* pathLabel;
    QFileSystemWatcher fsWatcher;
};
#endif // WATCHER_H
