#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
    namespace Ui { class SystemTray; }
QT_END_NAMESPACE

    class SystemTray : public QWidget
{
    Q_OBJECT

public:
    SystemTray(QWidget* parent = nullptr);
    ~SystemTray();

private slots:
    void on_toolButton_clicked();
    void on_actived(QSystemTrayIcon::ActivationReason reason);

    void on_pushButton_clicked();
    void on_action1();
    void on_action2();
    void on_action3();
    void on_action4();
private:
    void showWindow();
    Ui::SystemTray *ui;
    QSystemTrayIcon* m_systemTray;
    QMenu* m_menu;
    QAction* m_action1;
    QAction* m_action2;
    QAction* m_action3;
    QAction* m_action4;
};
#endif // SYSTEMTRAY_H
