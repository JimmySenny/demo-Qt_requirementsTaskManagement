#include <QApplication>

#include "rmtlogin.h"
#include "rmtmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RmtLogin w;
    w.show();

    return a.exec();
}
