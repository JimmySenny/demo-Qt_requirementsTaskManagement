#include "rmtmainwindow.h"
#include "ui_rmtmainwindow.h"

RmtMainWindow::RmtMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtMainWindow)
{
    ui->setupUi(this);
}

RmtMainWindow::~RmtMainWindow()
{
    delete ui;
}
