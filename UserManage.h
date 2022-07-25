#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QObject>
#include <QtSql>
#include <QCryptographicHash>

class UserManage : public QObject
{
    Q_OBJECT
public:
    explicit UserManage(QObject *parent = nullptr);

signals:

private:
    int userId;
    QString userName;
    QString passwd;
    int authority;

    QSqlDatabase usrDB;
    QSqlQuery *query;

    QString encrypt(const QString &str);

public:
    enum AUTHORITY_TYPE {
        ADMIN = 0,
        USER_FIRST_LEVEL,
        USER_SECOND_LEVEL,
        USER_THIRD_LEVEL,
        AUTHORITY_UNDIFINED
    };

    bool addUser(const QString &name, const QString &passwd, int authority, const QString email = "", const QString depart = "", const QString phoneNum = "");
    bool setUserInfo(const QString &name, const QString &passwd, int authority, const QString email = "", const QString depart = "", const QString phoneNum = "");
    bool deleteUser(const QString &name);
    bool deleteUser(int userId);
    int getUserId(const QString &name);
    int getUserAuthority(int userId);
    int getUserAuthority(const QString &name);
    bool hasUser(const QString &name);
    bool checkPassword(const QString &name, const QString &passwd);
    QSqlDatabase *getUserDb(void);

};

#endif // USERMANAGE_H
