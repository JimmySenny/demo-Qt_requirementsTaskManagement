#include <QApplication>

#include "rmt.h"
#include "rmtlogin.h"
#include "rmtcomm.h"

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    //Qt5.6 support HighDpi
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    RmtLogin w;
    w.show();
  /*
    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers);
    qDebug()<<driver;
   */
    return a.exec();
}
