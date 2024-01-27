#ifndef CONTACT_H
#define CONTACT_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>

class Contact :public QWidget
{
    Q_OBJECT
public:
    Contact(QWidget* parent = nullptr);
    ~Contact();
private:
    QLabel *emailLabel, *addressLabel, *codeLabel, *movtelLabel, *protalLabel;
    QLineEdit *emailEdit, *addressEdit, *codeEdit, *movtelEdit, *protelEdit;
    QCheckBox* movtelCheckBox;
    QGridLayout* mainLayout;
signals:
};

#endif // CONTACT_H
