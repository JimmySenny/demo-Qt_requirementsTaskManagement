#include "rmtconf.h"

RmtConf::RmtConf()
{

}

RmtConf::RmtConf(QString qstr_confm)

{

    if (qstr_confm.isEmpty())    {
        qstr_conf_file = QCoreApplication::applicationDirPath() + "\\RmtConf.ini";
    } else    {
        qstr_conf_file = qstr_confm;
    }
    qsetting = new QSettings(qstr_conf_file, QSettings::IniFormat);
    qDebug() << qstr_conf_file;
}



RmtConf::~RmtConf(){

    delete qsetting;

    qsetting = nullptr;

}



void RmtConf::SetConf(QString qstrnodename,QString qstrkeyname,QVariant qvarvalue){

    qsetting->setValue(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname), qvarvalue);

}



QVariant RmtConf::GetConf(QString qstrnodename,QString qstrkeyname)

{

    QVariant qvar = qsetting->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));

    return qvar;

}
