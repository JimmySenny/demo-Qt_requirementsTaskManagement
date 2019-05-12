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
    static DbMysql* getInstance();

    bool db_init(RmtConfValue *);
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
    static DbMysql* instance;
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DBMYSQL_H
