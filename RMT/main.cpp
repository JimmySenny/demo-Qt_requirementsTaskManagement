#include <QApplication>

#include "rmt.h"
#include "rmtlogin.h"
#include "rmtcomm.h"
#include "rmtconf.h"
#include "dbmysql.h"

int main_init(void);

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    //Qt5.6 support HighDpi
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

    if(!main_init()){
        //QMessageBox::information (&w, "警告", "应用程序初始化错误！");
        qDebug()<<"初始化错误";
        return -1;
    }

    RmtLogin w;
    w.show();

    return a.exec();
}

int
main_init_confisempty(RmtConfValue * confins){
    if ( 0 == (*confins->db_database).length() ||
         0 == (*confins->db_hostname).length() ||
         0 == (*confins->db_port).length() ||
         0 == (*confins->db_databasename).length() ||
         0 == (*confins->db_username).length() ||
         0 == (*confins->db_password).length() ){
        //emit signal_login_chk_err(ERR_CONF_ARGERR);
        //this->msg->show();
        qDebug() << "配置文件错误";
        return false;
    }
    return true;
}

int
main_init(void){
    /*
    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers);
    */
    //qDebug()<<QSqlDatabase::drivers();
    //qDebug()<<QCoreApplication::applicationDirPath();

    RmtConfValue * confins = RmtConfValue::getInstance();
    if ( !confins->conf_init() ){
        return false;
    }
    if ( !confins->getRmtConfValue() ){
        return false;
    }
    if ( !main_init_confisempty(confins)){
        return false;
    }

    DbMysql * dbins = DbMysql::getInstance();
    dbins->db_init(confins);

    return true;
}
