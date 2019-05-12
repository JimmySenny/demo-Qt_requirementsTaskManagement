#ifndef DBMYSQL_H
#define DBMYSQL_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "rmtcomm.h"
#include "rmtconf.h"

class DbMysql
{

public:
    //static DbMysql* getInstance();

    char a[100];
    QSqlDatabase db;

    DbMysql(RmtConfValue *);
    bool db_open();
    bool db_commit();
    bool db_rollback();
    void db_close();
    void db_test();
    bool query_chkuser(QString, QString);
    bool query_reqinput(QString, QString,QString);


private:
    DbMysql();
    ~DbMysql();
    //DbMysql* instance;
    QSqlQuery query;
};

#endif // DBMYSQL_H
