#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
class QDlgLogin;
}

class QDlgLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QDlgLogin(QWidget *parent = nullptr);
    ~QDlgLogin();


private slots:
    void on_btnLogin_clicked();

private:
    Ui::QDlgLogin *ui;
    QString m_user = "user";
    QString m_passwd = "12345";
    void readSettings();
    void writeSettings();
    QString encrypt(const QString &str);

};

#endif // QDLGLOGIN_H
