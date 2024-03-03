#ifndef PICTUREEDIT_H
#define PICTUREEDIT_H

//主窗口
#include <QMainWindow>
#include <QPixmap>
#include "photoshotdialog.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class PictureEdit; }
QT_END_NAMESPACE

    class PictureEdit : public QMainWindow
{
    Q_OBJECT

public:
    PictureEdit(QWidget *parent = nullptr);
    ~PictureEdit();
    void loadImage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PictureEdit *ui;
    QPixmap m_pixmap;
    PhotoShotDialog *m_psDialog;
};
#endif // PICTUREEDIT_H
