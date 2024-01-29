#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>
#include <QVBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();
    QLabel *nameLabel, *sexLabel, *ageLabel, *departmentLabel, *emailLabel;
    QLineEdit *nameLineEdit, *ageLineEdit, *emailLineEdit;
    QComboBox *sexcombobox, *departmentCombobox;
    QPushButton *okButton, *moreButton;
    QWidget *widget1, *widget2;
    QGridLayout *layout1, *layout2;
    QVBoxLayout* mainLayout;
private slots:
    void changeDialogSize();
};
#endif // DIALOG_H
