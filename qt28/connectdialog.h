#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtSql>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget* parent = nullptr);
    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;
    QSqlError addConnection(const QString& driver, const QString& dbName, const QString& host, const QString& user, const QString& passwd, int port = -1);
    void creatDB();
    void addSqliteConnection();
private slots:
    void on_cancelButton_clicked() { reject(); }
    void driverChanged(const QString&);
    void clickedButton1();
private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
