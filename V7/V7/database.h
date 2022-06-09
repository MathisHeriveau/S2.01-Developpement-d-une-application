#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QVariantList>

#define DATABASE_NAME "BD_NodenitBd1_Lakartxela"
#define CONNECT_TYPE "QODBC"


class DataBase
{
public:
    DataBase();
    bool openDataBase();
    void clseDataBase();
    bool restorDataBase();
    bool insertJoueur();
private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
