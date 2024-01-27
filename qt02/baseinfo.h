#ifndef BASEINFO_H
#define BASEINFO_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class Baseinfo : public QWidget {
    Q_OBJECT
public:
    Baseinfo(QWidget* parent = nullptr);
    ~Baseinfo();
private:
    QLabel *userNameLabel, *nameLabel, *sexLabel, *departmentLabel, *ageLabel, *otherLabel;
    QLineEdit *usernameEdit, *nameEdit, *ageEdit;
    QTextEdit* departmentEdit;
    QComboBox* sexEdit;
    QGridLayout* leftLayout; // 左边的格子布局
    QLabel *headLabel, *headPicLabel;
    QPushButton* updateHeadButton;
    QHBoxLayout* rightTopLayout; // 右上角的布局
    QLabel* introductionLabel;
    QTextEdit* introductionTextEdit;
    QVBoxLayout* rightLayout;  // 右边的布局

signals:

};

#endif // BASEINFO_H
