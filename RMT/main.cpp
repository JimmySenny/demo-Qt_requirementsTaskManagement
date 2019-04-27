#include <QApplication>

#include "rmtcomm.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RmtLogin w;
    w.show();
    DbMysql db;
    db.createConnection();
//    if( !db.createConnection() ) return false;

    return a.exec();
}
