#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class topWidget;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;

private slots:
    void on_actioncontent_triggered();

private:
    Ui::topWidget* ui;
    QTextEdit* m_textEdit;
    QTextDocument* m_document;
};
#endif // MAINWINDOW_H
