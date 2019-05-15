#include "dbmysql.h"

static int dbcount = 0;

DbMysql::DbMysql(){
    qDebug() << "DbMysql cons";
    dbcount++;
    //this->db = QSqlDatabase::database();
    //qDebug( "DbMysql[%p]", & this->db );
    //qDebug() << dbcount << this->db.isValid();
    //this->instance = this;
}

DbMysql::~DbMysql(){
    delete this;
    qDebug() << "~DbMysql()";
}


DbMysql* DbMysql::instance = new DbMysql();

DbMysql*
DbMysql::getInstance(){
    qDebug() << "DbMysql::getInstance()" << instance;
    //if ( dbcount < 1 ){
    //    DbMysql();
    //}
    //instance = this;
    return instance;
}

/*
DbMysql::DbMysql(RmtConfValue *conf_value)
{
    qDebug() << "DbMysql(RmtConfValue *)"<<*conf_value->db_database << *conf_value->db_username;
    if ( !QSqlDatabase::contains( "DbMysql" ) ){
        this->db = QSqlDatabase::addDatabase(*conf_value->db_database, "DbMysql" );
        //建立连接    数据TODO
        //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        //db.setHostName("localhost");
        this->db.setHostName(*conf_value->db_hostname);
        this->db.setPort((*conf_value->db_port).toInt());
        this->db.setDatabaseName(*conf_value->db_databasename);
        //db.setDatabaseName("mysql_odbc");
        this->db.setUserName(*conf_value->db_username);
        this->db.setPassword(*conf_value->db_password);
        this->query = QSqlQuery(this->db);
    } else {
        this->db = QSqlDatabase::database("DbMysql",true);
    }

    qDebug() << this->db.isValid();

    if( !this->db.open() ){
        qDebug() << "init1 open" << db.lastError();
    }
    qDebug() << "init2 open" << db.lastError();
    db.close();

}
*/
bool
DbMysql::db_init(RmtConfValue *conf_value){

    //qDebug() << "DbMysql(RmtConfValue *)"<<*conf_value->db_database << *conf_value->db_username;
    if ( !QSqlDatabase::contains( "DbMysql" ) ){
        this->db = QSqlDatabase::addDatabase(*conf_value->db_database, "DbMysql" );
        //建立连接    数据TODO
        //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        //db.setHostName("localhost");
        this->db.setHostName(*conf_value->db_hostname);
        this->db.setPort((*conf_value->db_port).toInt());
        this->db.setDatabaseName(*conf_value->db_databasename);
        //db.setDatabaseName("mysql_odbc");
        this->db.setUserName(*conf_value->db_username);
        this->db.setPassword(*conf_value->db_password);
        this->query = QSqlQuery(this->db);
    } else {
        this->db = QSqlDatabase::database("DbMysql",true);
    }

    qDebug() << "DbMysql::db_init" << this->db.isValid();

    return true;
}

bool
DbMysql::db_init(){
    if ( QSqlDatabase::contains( "DbMysql" ) ){
        this->db = QSqlDatabase::database("DbMysql",true);
    }else {
        return false;
    }

    qDebug() << "DbMysql::db_init" << this->db.isValid();
    return true;
}

bool
DbMysql::db_open()
{
    if ( !this->db.isValid() ){
        return false;
    }
    if ( !this->db.open()) {
        qDebug()  << "DbMysql::db_open()";
        QMessageBox::critical(nullptr, QObject::tr("db_open fail"), \
                              "db_open fail", QMessageBox::Cancel);
        return false;
    } else {
//       QMessageBox::critical(0, QObject::tr("db_open succ"), \
//        "", QMessageBox::Cancel);
    }

    return true;
}

bool
DbMysql::db_commit(){
    if( !this->db.commit() ){
        qDebug()  << "DbMysql::db_open()";
        return false;
    }
    return true;
}

bool
DbMysql::db_rollback(){
    if( !this->db.rollback() ){
        qDebug()  << "DbMysql::db_open()";
        return false;
    }
    return true;
}

void
DbMysql::db_close(){
    return this->db.close();
}

void
DbMysql::db_test(){
    qDebug() << "db_test():" << dbcount;
}


bool
DbMysql::query_chkuser(QString id, QString pwd ){
    if(!this->db_open()){
        return false;
    }
    qDebug() << "query_chkuser:" << __LINE__ << id << pwd;
    //QString chkuser = QString("select * from tb_rmt_user where user_id='"+id+"' and user_pwd='"+pwd);
    //QString chkuser = QString("select * from rmt_user ");
    //qDebug() << chkuser;
    //  query.exec(chkuser);
    //this->query =  QSqlQuery( chkuser );
    //QSqlRecord rec = query.record();
    //QSqlRecord rec = query.isSelect();
    //qDebug() << "query:" << query.isSelect();
    this->query = QSqlQuery(QString("select * from tb_rmt_user where user_id=%1 and user_pwd=%2").arg(id).arg(pwd),db);

    if(!query.next()){
         return false;
    }

    this->db_close();
    return true;
}
bool
DbMysql::query_reqinput(QString uuid, QString req_no, QString inputdt ){
    qDebug()  << "query_reqinput";
    if(!this->db_open()){
        return false;
    }
    //this->query = QSqlQuery(QString("insert into tb_rmt_requirements ? uuid,req_no,req_inputdt) values( %1,%2,%3").arg(uuid).arg(req_no).arg(inputdt));
    this->query.prepare("insert into tb_rmt_requirements (uuid,req_no,req_inputdt) \
                        values(:uuid, :req_no, :req_inputdt) " );
    this->query.bindValue(":uuid", uuid);
    this->query.bindValue(":req_no", req_no);
    this->query.bindValue(":req_inputdt", inputdt);

    if(!query.exec()){
        return false;
    }
    qDebug()  << "query_reqinput:exec succ";
    this->db_close();
    return true;
}
