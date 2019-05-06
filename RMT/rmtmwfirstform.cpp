#include "rmtmwfirstform.h"
#include "ui_rmtmwfirstform.h"

RmtmwFirstForm::RmtmwFirstForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwFirstForm)
{
    ui->setupUi(this);
}

RmtmwFirstForm::~RmtmwFirstForm()
{
    delete ui;
}
