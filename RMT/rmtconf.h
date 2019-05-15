#ifndef RMTCONF_H
#define RMTCONF_H

#include <QVariant>
#include <QSettings>

#include "rmtcomm.h"

class RmtConfFunc
{
public:
    RmtConfFunc();
    RmtConfFunc(QString qstr_confm);
    virtual ~RmtConfFunc(void);
    bool initConf(QString);
    QVariant GetConf(QString,QString);
    void SetConf(QString,QString,QVariant);
private:
    QString  fileconf_name;
    QSettings * qsetting;
};

class RmtConfValue{
public:

    ~RmtConfValue();
    static RmtConfValue* getInstance();
    bool conf_init();

  QString *user_id;
  QString *user_pwd;
  QString *db_database;
  QString *db_hostname;
  QString *db_port;
  QString *db_databasename;
  QString *db_username;
  QString *db_password;



  bool getRmtConfValue();
  void setRmtConfValue(RmtConfValue *);
  RmtConfFunc *conffunc;

private:
    static RmtConfValue* instance;
    RmtConfValue();
    QString * pfileconf_name;
    QFileInfo * pfileconf_info;
};



#endif // RMTCONF_H
