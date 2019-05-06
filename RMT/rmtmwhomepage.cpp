#include "rmtmwhomepage.h"
#include "ui_rmtmwhomepage.h"

RmtmwHomePage::RmtmwHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwHomePage)
{
    ui->setupUi(this);
}

RmtmwHomePage::~RmtmwHomePage()
{
    delete ui;
}
