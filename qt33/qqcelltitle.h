#ifndef QQCELLTITLE_H
#define QQCELLTITLE_H

#include <QWidget>

namespace Ui {
class QQCellTitle;
}

class QQCellTitle : public QWidget
{
    Q_OBJECT

public:
    explicit QQCellTitle(QString groupName, QWidget* parent = nullptr);
    ~QQCellTitle();
    void setOnlineAndGroup(int onlineCount = 0, int groupCount = 0);
    bool eventFilter(QObject* watched, QEvent* event);
private:
    Ui::QQCellTitle* ui;
    bool m_isOpen;
    bool m_cellIsHover;
signals:
    void sigCellStatusChange(bool);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // QQCELLTITLE_H
