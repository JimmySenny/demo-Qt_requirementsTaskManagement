#include "rmtmainwindow.h"
#include "ui_rmtmainwindow.h"

RmtMainWindow::RmtMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtMainWindow)
{
    ui->setupUi(this);
    rmw_init();
}

RmtMainWindow::~RmtMainWindow()
{
    delete ui;
}

//QListWidget QTreeWidget
//QStackedWidget QTabWidget

bool
RmtMainWindow::rmw_init(){
    this->label_1 = new QLabel("a");
    //this->lable_1 = new QLable("b");
    this->ui->listWidget->addItem("this->label_1");
    //this->ui->listWidget->addItem(this->lable_2);
    return true;
}
