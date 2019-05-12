#include <QApplication>

#include "rmt.h"
#include "rmtlogin.h"
#include "rmtcomm.h"
#include "dbmysql.h"

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    //Qt5.6 
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers);
    qDebug()<<drivers;

    DbMysql * dbmysql = DbMysql::getInstance();

    RmtLogin w;
    w.show();

    return a.exec();
}
