#include "rmtmwthirdform.h"
#include "ui_rmtmwthirdform.h"

RmtmwThirdForm::RmtmwThirdForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwThirdForm)
{
    ui->setupUi(this);
}

RmtmwThirdForm::~RmtmwThirdForm()
{
    delete ui;
}
