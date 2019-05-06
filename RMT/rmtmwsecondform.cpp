#include "rmtmwsecondform.h"
#include "ui_rmtmwsecondform.h"

RmtmwSecondForm::RmtmwSecondForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwSecondForm)
{
    ui->setupUi(this);
}

RmtmwSecondForm::~RmtmwSecondForm()
{
    delete ui;
}
