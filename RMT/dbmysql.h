#ifndef DBMYSQL_H
#define DBMYSQL_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "rmtcomm.h"
#include "rmtconf.h"

class DbMysql
{

public:

    DbMysql(RmtConfValue *);
    bool db_open();
    bool db_commit();
    bool db_rollback();
    void db_close();
    bool query_chkuser(QString, QString);
    bool query_reqinput(QString, QString,QString);

private:
    DbMysql();
    QSqlDatabase db;
    QSqlQuery query;
    static DbMysql dbsql;
};

#endif // DBMYSQL_H
