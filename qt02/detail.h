#ifndef DETAIL_H
#define DETAIL_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QTextEdit>


class Detail :public QWidget
{
    Q_OBJECT
public:
    Detail(QWidget* parent = nullptr);
    ~Detail();

private:
    QLabel *nationLabel, *provinceLabel, *cityLabel, *introductLabel;
    QLineEdit* cityEdit;
    QComboBox *nationEdit, *provinceEdit;
    QTextEdit* introductionEdit;
    QGridLayout* mainLayout;
signals:
};

#endif // DETAIL_H
