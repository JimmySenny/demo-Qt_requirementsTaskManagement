#ifndef RMTMWREQINPUTFORM_H
#define RMTMWREQINPUTFORM_H

#include <QWidget>

#include "rmtcomm.h"
#include "rmtsyspara.h"
#include "rmtmessagebox.h"
#include "dbmysql.h"
#include "rmtconf.h"



namespace Ui {
class RmtmwReqInputForm;
}

class RmtmwReqInputForm : public QWidget
{
    Q_OBJECT

signals:
    void    signal_login_chk_err(int);

public:
    explicit RmtmwReqInputForm(QWidget *parent = nullptr);
    ~RmtmwReqInputForm();

    bool rmw_reqinput_init();

public slots:
    void slot_on_pushButton_commit_clicked();

private:
    Ui::RmtmwReqInputForm *ui;
    RmtMessageBox * msg;
    RmtConfValue * confins;
    DbMysql * dbins;
};

#endif // RMTMWFIRSTFORM_H
