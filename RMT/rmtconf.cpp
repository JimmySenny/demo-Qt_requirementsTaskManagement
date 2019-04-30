#include "rmtconf.h"

RmtConfFunc::RmtConfFunc(){

}

RmtConfFunc::RmtConfFunc(QString qstr_confm){
    if (qstr_confm.isEmpty())    {
        rmtconf_file = QCoreApplication::applicationDirPath() + "\\RmtConf.ini";
    } else    {
        rmtconf_file  = qstr_confm;
    }
    qDebug() << rmtconf_file;
    qsetting = new QSettings(rmtconf_file, QSettings::IniFormat);
}



RmtConfFunc::~RmtConfFunc(){
  delete qsetting;
  qsetting = nullptr;
}



void RmtConfFunc::SetConf(QString qstrnodename,QString qstrkeyname,QVariant qvarvalue){
  qsetting->setValue(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname), qvarvalue);
}



QVariant RmtConfFunc::GetConf(QString qstrnodename,QString qstrkeyname){
  QVariant qvar = qsetting->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));
  return qvar;
}


RmtConfValue::RmtConfValue(){

#ifdef Q_OS_UNIX
  conf_file = new QString("~/RmtConf.ini");
#endif
#ifdef Q_OS_WIN
  conf_file = new QString(QCoreApplication::applicationDirPath()+"/RmtConf.ini");
#endif

}

RmtConfValue::~RmtConfValue(){
  delete this->user_id;
  this->user_id = nullptr;
}

bool
RmtConfValue::getRmtConfValue(){
  QFileInfo fileinfo(*conf_file);
  if ( !fileinfo.isFile( ) ){
      QMessageBox::critical(0, QObject::tr("配置文件错误"), \
                            "无法打开配置文件！ ", QMessageBox::Cancel);
      qDebug() << "RmtConfValue配置文件不存在";
      return false;
  }
  this->conf = new RmtConfFunc(QCoreApplication::applicationDirPath()+"/rmtconf.ini");

  this->user_id = new QString ( this->conf->GetConf("USER","user_id").toString());
  this->user_pwd = new QString ( this->conf->GetConf("USER","user_pwd").toString());

  this->db_database = new QString ( this->conf->GetConf("DATABASE","db_database").toString());
  this->db_hostname = new QString ( this->conf->GetConf("DATABASE","db_hostname").toString());
  this->db_port = new QString ( this->conf->GetConf("DATABASE","db_port").toString());
  this->db_databasename = new QString ( this->conf->GetConf("DATABASE","db_databasename").toString());
  this->db_username = new QString ( this->conf->GetConf("DATABASE","db_username").toString());
  this->db_password = new QString ( this->conf->GetConf("DATABASE","db_password").toString());

  qDebug() << *this->user_id;
  return true;
}

void
RmtConfValue::setRmtConfValue(RmtConfValue * confvalue){
  qDebug() << *confvalue->user_id;
  this->conf->SetConf("USER","user_id",*confvalue->user_id);
  this->conf->SetConf("USER","user_pwd",*confvalue->user_pwd);
}
