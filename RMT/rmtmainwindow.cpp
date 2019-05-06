#include "rmtmainwindow.h"
#include "ui_rmtmainwindow.h"

RmtMainWindow::RmtMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtMainWindow)
{
    ui->setupUi(this);
    rmw_init();
    /* connect(this->ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),\ */
    connect(this->ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),\
            this,SLOT(on_treeWidget_itemClicked(QTreeWidgetItem*,int)));
}

RmtMainWindow::~RmtMainWindow()
{
    delete ui;
}

//QListWidget QTreeWidget
//QStackedWidget QTabWidget

void
RmtMainWindow::rmw_switchForm(int idx ){

    //this->ui->stackedWidget->setCurrentIndex( idx );
    qDebug() << idx;
    //qDebug() << this->ui->stackedWidget->currentWidget();
}

bool
RmtMainWindow::rmw_init(){
    //this->phomepage = new RmtmwHomePage(this->ui->page_0);
    //this->pfirstform = new RmtmwFirstForm(this->ui->page_1);
    //this->psecondform = new RmtmwSecondForm(this->ui->page_2);
    //this->pthirdform = new RmtmwThirdForm(this->ui->page_3);

    //this->ui->page_0->show();

    //this->ui->page_0

    //this->ui- ->addWidget(phomepage);
    //this->ui->stackedWidget->addWidget(pfirstform);
    //this->ui->stackedWidget->addWidget(psecondform);

    //this->ui->stackedWidget->setCurrentWidget(phomepage);

    return true;
}

void
RmtMainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column){
    qDebug() << item->text(0)  ;

    if (!QString::compare ( item->text(0),"0",Qt::CaseInsensitive) ) {
        qDebug() << "switch home";
        rmw_switchForm(0);
        //this->ui->stackedWidget->setCurrentWidget(pfirstform);
    } else if (!QString::compare ( item->text(0),"R",Qt::CaseInsensitive) ) {
        qDebug() << "switch first";
        rmw_switchForm(1);
        //this->ui->stackedWidget->setCurrentWidget(pfirstform);
    }else if (!QString::compare( item->text(0), "T",Qt::CaseInsensitive)){
        qDebug() << "switch second";
        rmw_switchForm(2);
        //this->ui->stackedWidget->setCurrentWidget(psecondform);
    }else if (!QString::compare( item->text(0), "M",Qt::CaseInsensitive)){
        qDebug() << "switch third";
        rmw_switchForm(3);
        //this->ui->stackedWidget->setCurrentWidget(psecondform);
    }else {
        qDebug() << "switch homepage";
        rmw_switchForm(0);
        //this->ui->stackedWidget->setCurrentWidget(phomepage);
    }
}

