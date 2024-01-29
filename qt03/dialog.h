#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
    namespace Ui { class Dialog; }
QT_END_NAMESPACE

    class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();
    void createLeftFrame();
    void createRightFrame();
    void fillColorList(QComboBox* combobox);
private slots:
    void showWindow();
    void showWindowText();
    void showButton();
    void showButtonText();
    void showBase();

private:
    QFrame *leftFrame, *rightFrame;
    QLabel *windowLabel, *windowTextLabel, *buttonLabel, *buttonTextLabel, *baseLabel;
    QComboBox *windowcombobox, *windowTextCombobox, *buttonCombobox, *buttonTextCombobox, *baseCombobox;
    QLabel *label1, *label2;
    QComboBox* combobox;
    QLineEdit* lineEdit;
    QTextEdit* textEdit;
    QPushButton* okButton,*cancelButton;

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
