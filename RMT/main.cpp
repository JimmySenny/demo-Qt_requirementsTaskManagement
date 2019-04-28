#include <QApplication>

#include "rmt.h"
#include "rmtlogin.h"
#include "rmtmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RmtLogin w;
    w.show();

    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers)
    qDebug()<<driver;

    return a.exec();
}
