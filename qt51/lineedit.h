#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = nullptr);

private:
    int m_count_key = 0;
protected:
    virtual void keyPressEvent(QKeyEvent * event) override;
};

#endif // LINEEDIT_H
