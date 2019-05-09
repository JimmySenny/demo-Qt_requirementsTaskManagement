#include "dbmysql.h"

DbMysql::DbMysql(){

}

DbMysql::DbMysql(RmtConfValue *conf_value)
{
  qDebug() << "DbMysql(RmtConfValue *)"<<*conf_value->db_database;
  this->db =  QSqlDatabase::addDatabase( *conf_value->db_database);
  //建立连接    数据TODO
  //QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  //db.setHostName("localhost");
  this->db.setHostName(*conf_value->db_hostname);
  this->db.setPort((*conf_value->db_port).toInt());
  this->db.setDatabaseName(*conf_value->db_databasename);       //这里输入� 的数据库名
  //db.setDatabaseName("mysql_odbc");
  this->db.setUserName(*conf_value->db_username);
  this->db.setPassword(*conf_value->db_password);   //这里输入� 的密� �
  this->query = QSqlQuery(this->db);
}

bool
DbMysql::db_open()
{
  if (!db.open()) {
//       QMessageBox::critical(0, QObject::tr("� 法打开数据库"),
//      "� 法创建数据库连接！ ", QMessageBox::Cancel);
        return false;
  } else {
//       QMessageBox::critical(0, QObject::tr("打开数据库成功"),
//        "成功创建数据库连接！ ", QMessageBox::Cancel);
  }

    return true;
}

bool
DbMysql::db_commit(){
  if( !db.commit() ){
      return false;
  }
  return true;
}

bool
DbMysql::db_rollback(){
  if( !db.rollback() ){
      return false;
  }
  return true;
}

void
DbMysql::db_close(){
  return db.close();
}

bool
DbMysql::query_chkuser(QString id, QString pwd ){

  if(!this->db_open()){
      return false;
  }
    //QString chkuser = QString("select * from tb_rmt_user where user_id='"+id+"' and user_pwd='"+pwd);
    //QString chkuser = QString("select * from rmt_user ");
    //qDebug() << chkuser;
    //  query.exec(chkuser);
    //this->query =  QSqlQuery( chkuser );
    //QSqlRecord rec = query.record();
    //QSqlRecord rec = query.isSelect();
    //qDebug() << "query:" << query.isSelect();

    this->query = QSqlQuery(QString("select * from tb_rmt_user where user_id=%1 and user_pwd=%2").arg(id).arg(pwd));

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

     this->db_close();
     return true;
}
