#include "rmtconf.h"

RmtConfFunc::RmtConfFunc(){

}

RmtConfFunc::RmtConfFunc(QString qstr_confm){
    if (qstr_confm.isEmpty())    {
        fileconf_name = QCoreApplication::applicationDirPath() + "\\RmtConf.ini";
    } else    {
        fileconf_name  = qstr_confm;
    }
    qDebug() << fileconf_name;
    qsetting = new QSettings(fileconf_name, QSettings::IniFormat);
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
    qDebug() << "RmtConfValue cons";
    pfileconf_name = new QString("RmtConf.ini");

    //RmtConfValue conffunc = new RmtConfFunc::RmtConfFunc();

}

RmtConfValue::~RmtConfValue(){
  delete this->user_id;
  this->user_id = nullptr;
}

RmtConfValue* RmtConfValue::instance = new RmtConfValue();

RmtConfValue*
RmtConfValue::getInstance(){
    qDebug() << "RmtConfValue::getInstance():" << instance ;

    return instance;
}

bool
RmtConfValue::conf_init(){

#ifdef Q_OS_UNIX
    fileconf_name = new QString("~/RmtConf.ini");
#endif
#ifdef Q_OS_WIN
    pfileconf_name = new QString(QCoreApplication::applicationDirPath()+"/RmtConf.ini");
#endif

    //QFileInfo fileinfo( *conf_file );
    qDebug() <<"RmtConfValue::conf_init"<< *pfileconf_name;
    pfileconf_info = new QFileInfo( *pfileconf_name);

    if ( !(pfileconf_info->isFile()) ){
        QMessageBox::critical(0, QObject::tr("配置文件错误"), \
                              "无法打开配置文件！ ", QMessageBox::Cancel);
        qDebug() << "RmtConfValue配置文件不存在";
        return false;
    }
    this->conffunc = new RmtConfFunc(QCoreApplication::applicationDirPath()+"/RmtConf.ini");
    return true;
}

bool
RmtConfValue::getRmtConfValue(){

  this->user_id = new QString ( this->conffunc->GetConf("USER","user_id").toString());
  this->user_pwd = new QString ( this->conffunc->GetConf("USER","user_pwd").toString());

  this->db_database = new QString ( this->conffunc->GetConf("DATABASE","db_database").toString());
  this->db_hostname = new QString ( this->conffunc->GetConf("DATABASE","db_hostname").toString());
  this->db_port = new QString ( this->conffunc->GetConf("DATABASE","db_port").toString());
  this->db_databasename = new QString ( this->conffunc->GetConf("DATABASE","db_databasename").toString());
  this->db_username = new QString ( this->conffunc->GetConf("DATABASE","db_username").toString());
  this->db_password = new QString ( this->conffunc->GetConf("DATABASE","db_password").toString());

  qDebug() << "RmtConfValue::getRmtConfValue:" << *this->user_id;
  return true;
}

void
RmtConfValue::setRmtConfValue(RmtConfValue * confvalue){
  qDebug() << *confvalue->user_id;
  this->conffunc->SetConf("USER","user_id",*confvalue->user_id);
  this->conffunc->SetConf("USER","user_pwd",*confvalue->user_pwd);
}
