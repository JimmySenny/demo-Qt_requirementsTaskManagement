#ifndef DBMYSQL_H
#define DBMYSQL_H


#include <QSqlDatabase>
#include <QSqlQuery>

#include "rmtcomm.h"

class DbMysql
{
public:
    DbMysql();
    bool createConnection();
};

#endif // DBMYSQL_H
