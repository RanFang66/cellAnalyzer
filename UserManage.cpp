#include "UserManage.h"

UserManage::UserManage(QObject *parent)
    : QObject{parent}
{
    usrDB = QSqlDatabase::addDatabase("QSQLITE");
    usrDB.setDatabaseName("UserInfo.db");

    if (!usrDB.open()) {
        qDebug() << "Open User Information Database Failed!" << Qt::endl;
    }

    query = new QSqlQuery(usrDB);
}

QString UserManage::encrypt(const QString &str)
{
    QByteArray btArray;
    btArray.append(str.toLatin1());
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(btArray);
    QByteArray resultArray = hash.result();
    QString md5 = resultArray.toHex();
    return md5;
}

bool UserManage::addUser(const QString &name, const QString &passwd, int authority, const QString email, const QString depart, const QString phoneNum)
{
    bool ret = false;

    query->prepare(R"(INSERT INTO user_info_table(name, passwd, authority, email, depart, phone) VALUES(?, ?, ?, ?, ?, ?);)");
    query->addBindValue(name);
    query->addBindValue(encrypt(passwd));
    query->addBindValue(authority);
    query->addBindValue(email);
    query->addBindValue(depart);
    query->addBindValue(phoneNum);

    ret = query->exec();
    query->clear();
    return ret;
}

bool UserManage::setUserInfo(const QString &name, const QString &passwd, int authority, const QString email, const QString depart, const QString phoneNum)
{
    bool ret = false;

    query->prepare(R"(INSERT INTO user_info_table(name, passwd, authority, email, depart, phone) VALUES(?, ?, ?, ?, ?, ?);)");
    query->addBindValue(name);
    query->addBindValue(encrypt(passwd));
    query->addBindValue(authority);
    query->addBindValue(email);
    query->addBindValue(depart);
    query->addBindValue(phoneNum);

    ret = query->exec();
    query->clear();
    return ret;
}

bool UserManage::deleteUser(const QString &name)
{
    bool ret;
    ret = query->exec(QString(R"(DELETE FROM user_info_table WHERE name = '%1)").arg(name));
    query->clear();

    return ret;
}

bool UserManage::deleteUser(int userId)
{
    bool ret;
    ret = query->exec(QString(R"(DELETE FROM user_info_table WHERE userId = '%1)").arg(userId));
    query->clear();

    return ret;

}

int UserManage::getUserId(const QString &name)
{
    int id = -1;
    bool ret;
    ret = query->exec(QString(R"(SELECT ID FROM user_info_table WHERE name = '%1')").arg(name));
    if (ret) {
        ret = query->next();
        if (ret) {
           id = query->value(0).toInt();
        }
    }
    return id;
}

int UserManage::getUserAuthority(int userId)
{
    int authority = -1;
    bool ret = false;
    ret = query->exec(QString(R"(SELECT authority FROM user_info_table WHERE ID= %1)").arg(userId));
    if (ret) {
        ret = query->next();
        if (ret) {
           authority = query->value(0).toInt();
        }
    }
    return authority;

}

int UserManage::getUserAuthority(const QString &name)
{
    int authority = -1;
    bool ret = false;
    ret = query->exec(QString(R"(SELECT authority FROM user_info_table WHERE name = '%1')").arg(name));
    if (ret) {
        ret = query->next();
        if (ret) {
           authority = query->value(0).toInt();
        }
    }
    return authority;

}

bool UserManage::hasUser(const QString &name)
{
    bool ret;
    ret = query->exec(QString(R"(SELECT id FROM user_info_table WHERE name = %1)").arg(name));
    if (ret) {
        ret = query->next();
    }
    return ret;
}

bool UserManage::checkPassword(const QString &name, const QString &passwd)
{
    bool ret = false;
    QString pswd_md5;

    if (query->exec(QString(R"(SELECT password FROM user_info_table WHERE name = '%1')").arg(name))) {
        if (query->next()){
            pswd_md5 = query->value(0).toString();
            ret = (pswd_md5 == passwd);
        }
    }
    return ret;
}

QSqlDatabase *UserManage::getUserDb()
{
    return &usrDB;
}
