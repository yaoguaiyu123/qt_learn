#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QString>
#include "showwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private:
    QMenu* fileMenu;
    QMenu* zoomMenu;
    QMenu* rotateMenu;
    QMenu* mirrorMenu;
    QImage img;
    QString filename;
    ShowWidget* showWidget; // 子控件
    QAction *openFileAction, *newFileAction, *printTextAction, *printImageAction, *exitAction, *copyAction, *cutAction,
        *pasteAction, *aboutAction, *zoomInAction, *zoomOutAction, *rotate90Action, *rotate180Action, *rotate270Action,
        *mirrorVAction, *mirrorHAction, *undoAction, *redoAction;
    QToolBar *filetool, *zoomtool, *rotatetool, *mirrortool, *dotool;
};
#endif // MAINWINDOW_H









