#include <QApplication>

<<<<<<< HEAD
#include "rmt.h"
#include "rmtlogin.h"
#include "rmtmainwindow.h"
=======
#include "rmtcomm.h"


>>>>>>> d941d8facdd3209bfd7c19b9dba421f9731fc621

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RmtLogin w;
    w.show();
    DbMysql db;
    db.createConnection();
//    if( !db.createConnection() ) return false;

    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers)
    qDebug()<<driver;

    return a.exec();
}
