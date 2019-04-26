#include "rmtmessagebox.h"
#include "ui_rmtmessagebox.h"

RmtMessageBox::RmtMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RmtMessageBox)
{
    ui->setupUi(this);
}

/*
RmtMessageBox::RmtMessageBox(QString retcode, QString errmsg,QWidget *parent ):
    QDialog(parent),
    ui(new Ui::RmtMessageBox)
{
    ui->setupUi(this);
    ui->textBrowser->setText("");
}
*/

RmtMessageBox::~RmtMessageBox()
{
    delete ui;
}

void
RmtMessageBox::slot_msgbox_set_code(int code){
    char tmp[1024+1];
    sprintf(tmp,"%d", code);

    this->ui->textBrowser->setText(tmp);
}
