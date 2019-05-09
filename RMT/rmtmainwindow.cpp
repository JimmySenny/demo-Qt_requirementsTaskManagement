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
    connect(this->ui->tabWidget,SIGNAL(tabCloseRequested(int )), \
            this->ui->tabWidget,SLOT(on_tabWidget_tabCloseRequested(int)));
}

RmtMainWindow::~RmtMainWindow()
{
    delete ui;
}

//QListWidget QTreeWidget
//QStackedWidget QTabWidget

void
RmtMainWindow::rmw_switchForm(QWidget * p_page ){
    qDebug() << p_page;
    //this->ui->stackedWidget->setCurrentIndex( idx );
    //qDebug() << this->ui->stackedWidget->currentWidget();

    this->ui->tabWidget->setCurrentWidget( p_page );
}

bool
RmtMainWindow::rmw_init(){
    this->phomepage = this->ui->tab;
    this->preqselectform = new RmtmwReqSelectForm(this->ui->tabWidget);
    this->preqinputform = new RmtmwReqInputForm(this->ui->tabWidget);
    //this->ui->page_0->show();

    //this->ui->stackedWidget->addWidget(pfirstform);
    //this->ui->stackedWidget->addWidget(psecondform);

    //this->ui->stackedWidget->setCurrentWidget(phomepage);

    this->ui->tabWidget->setCurrentIndex(0);
    this->preqselectform->hide();
    this->preqinputform->hide();

    return true;
}

void
RmtMainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column){
    qDebug() << item->text(0)  ;

    if (!QString::compare ( item->text(0),"0",Qt::CaseInsensitive) ) {
        qDebug() << "switch home";
        rmw_switchForm(0);
        //this->ui->stackedWidget->setCurrentWidget(pfirstform);
    } else if (!QString::compare ( item->text(0),"R0",Qt::CaseInsensitive) ) {
        qDebug() << "switch zero";
        if ( this->ui->tabWidget->indexOf(preqselectform) < 0 ) {
            this->ui->tabWidget->insertTab(1,preqselectform,"R0");
            //this->ui->tabWidget->addTab(psecondform,"RRRR");
        }
        qDebug() << this->ui->tabWidget->indexOf(preqinputform);
        rmw_switchForm(preqselectform);
    } else if (!QString::compare ( item->text(0),"R1",Qt::CaseInsensitive) ) {
        qDebug() << "switch first";
        if ( this->ui->tabWidget->indexOf(preqinputform) < 0 ) {
            this->ui->tabWidget->insertTab(2,preqinputform,"R1");
            //this->ui->tabWidget->addTab(psecondform,"RRRR");
        }
        qDebug() << this->ui->tabWidget->indexOf(preqinputform);
        rmw_switchForm(preqinputform);
    }else {
        qDebug() << "switch homepage";
        rmw_switchForm(phomepage);
    }
}


void RmtMainWindow::on_tabWidget_tabCloseRequested(int index){
    if  ( 0 == index ) {
        return;
    }
    this->ui->tabWidget->removeTab(index);
}
