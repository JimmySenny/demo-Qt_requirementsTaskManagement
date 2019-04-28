#include "dbmysql.h"

DbMysql::DbMysql()
{

}

bool
DbMysql::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    //db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("rmtdb");       //这里输入你的数据库名
    //db.setDatabaseName("mysql_odbc");
    db.setUserName("rmt");
    db.setPassword("123456");   //这里输入你的密码
    if (!db.open()) {
   //     QMessageBox::critical(0, QObject::tr("无法打开数据库"),
   //    "无法创建数据库连接！ ", QMessageBox::Cancel);
        return false;
    } else {
    //    QMessageBox::critical(0, QObject::tr("打开数据库成功"),
    //    "成功创建数据库连接！ ", QMessageBox::Cancel);
    }

    return true;
}
