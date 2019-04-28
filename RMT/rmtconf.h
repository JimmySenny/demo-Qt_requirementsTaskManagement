#ifndef RMTCONF_H
#define RMTCONF_H

#include <QVariant>
#include <QSettings>
#include <QString>

#include "rmtcomm.h"

class RmtConf
{
public:
    RmtConf();
    RmtConf(QString qstr_confm);
    virtual ~RmtConf(void);
    void SetConf(QString,QString,QVariant);
    QVariant GetConf(QString,QString);
private:
    QString qstr_conf_file;
    QSettings * qsetting;
};

#endif // RMTCONF_H
