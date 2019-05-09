#ifndef RMTMAINWINDOW_H
#define RMTMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "rmtcomm.h"

#include "rmtmwhomepage.h"
#include "rmtmwreqselectform.h"
#include "rmtmwreqinputform.h"

namespace Ui {
class RmtMainWindow;
}

class RmtMainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    //void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_tabWidget_tabCloseRequested(int index);

public:
    explicit RmtMainWindow(QWidget *parent = nullptr);
    ~RmtMainWindow();
    bool rmw_init();
    void rmw_switchForm(QWidget *);

private slots:


private:
    Ui::RmtMainWindow *ui;

    RmtmwHomePage * phomepage;
    RmtmwReqSelectForm * preqselectform;
    RmtmwReqInputForm * preqinputform;

};

#endif // RMTMAINWINDOW_H
