#ifndef RMTMAINWINDOW_H
#define RMTMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "rmtcomm.h"

#include "rmtmwhomepage.h"
#include "rmtmwfirstform.h"
#include "rmtmwsecondform.h"
#include "rmtmwthirdform.h"

namespace Ui {
class RmtMainWindow;
}

class RmtMainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    //void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

public:
    explicit RmtMainWindow(QWidget *parent = nullptr);
    ~RmtMainWindow();
    bool rmw_init();
    void rmw_switchForm(int index);

private:
    Ui::RmtMainWindow *ui;

    RmtmwHomePage * phomepage;
    RmtmwFirstForm * pfirstform;
    RmtmwSecondForm * psecondform;
    RmtmwThirdForm * pthirdform;

};

#endif // RMTMAINWINDOW_H
