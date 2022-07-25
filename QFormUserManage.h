#ifndef QFORMUSERMANAGE_H
#define QFORMUSERMANAGE_H

#include <QWidget>
#include <UserManage.h>

namespace Ui {
class QFormUserManage;
}

class QFormUserManage : public QWidget
{
    Q_OBJECT

public:
    explicit QFormUserManage(QWidget *parent = nullptr);
    ~QFormUserManage();

private slots:
    void on_btnAddUser_clicked();

private:
    Ui::QFormUserManage *ui;
    QSqlDatabase *userDb;

    QString currName;
    QString passwd;
    QString passwdConfirm;
    QString email;
    QString department;
    QString phone;
};

#endif  // QFORMUSERMANAGE_H
