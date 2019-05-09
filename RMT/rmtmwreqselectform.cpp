#include "rmtmwreqselectform.h"
#include "ui_rmtmwreqselectform.h"

RmtmwReqSelectForm::RmtmwReqSelectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwReqSelectForm)
{
    ui->setupUi(this);
}

RmtmwReqSelectForm::~RmtmwReqSelectForm()
{
    delete ui;
}
