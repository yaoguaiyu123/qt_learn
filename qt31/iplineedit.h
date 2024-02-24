#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include <QLineEdit>
#include <QObject>
#define IP_INPUT_SIZE 4

class IPLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    IPLineEdit(QWidget* widget = 0);
    ~IPLineEdit();
    QString text();

private:
    QLineEdit* m_lineEdits[IP_INPUT_SIZE];
    int getIndex(QLineEdit* pLineEdit);
protected:
    bool eventFilter(QObject* watched, QEvent* event);
};

#endif // IPLINEEDIT_H
