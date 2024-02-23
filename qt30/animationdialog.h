#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>
#include "animationstackwidget.h"
#include "page01.h"
#include "page02.h"

class AnimationDialog : public QDialog
{
public:
    AnimationDialog();


private:
    AnimationStackWidget* m_asw;
    Page01* m_page01;
    Page02* m_page02;
private slots:
    void onPage01Clicked();
    void onPage02Clicked();
};

#endif // ANIMATIONDIALOG_H
