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
    QString  rmtconf_file;
    QSettings * qsetting;
};

class RmtConfValue{
public:

  QString *user_id;
  QString *user_pwd;
  QString *db_database;
  QString *db_hostname;
  QString *db_port;
  QString *db_databasename;
  QString *db_username;
  QString *db_password;

  RmtConfValue();
  ~RmtConfValue();
  bool getRmtConfValue();
  void setRmtConfValue(RmtConfValue *);
  RmtConfFunc * conf;
  QString * conf_file;
};



#endif // RMTCONF_H
