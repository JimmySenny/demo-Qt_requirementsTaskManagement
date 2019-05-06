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

    this->ui->stackedWidget->setCurrentIndex( idx );
    qDebug() << this->ui->stackedWidget->currentWidget();
}

bool
RmtMainWindow::rmw_init(){
    this->phomepage = new RmtmwHomePage(this);
    this->pfirstform = new RmtmwFirstForm(this);
    this->psecondform = new RmtmwSecondForm(this);

    this->ui->stackedWidget->addWidget(phomepage);
    this->ui->stackedWidget->addWidget(pfirstform);
    this->ui->stackedWidget->addWidget(psecondform);

    this->ui->stackedWidget->setCurrentWidget(phomepage);

    return true;
}

void
RmtMainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column){
    qDebug() << item->text(0) << "column:"<< column ;
    //QString itemText=item->text(0);//获取选中的名字
    //qDebug("SelectName = %s",qPrintable(itemText));

    qDebug() << item->text(0) << item->textAlignment(0);
    //item->setText(0, "test");
    if (!QString::compare ( item->text(0),"subtree1",Qt::CaseInsensitive) ) {
        qDebug() << "switch first";
        rmw_switchForm(1);
        //this->ui->stackedWidget->setCurrentWidget(pfirstform);
    }else if (!QString::compare( item->text(0), "subtree2",Qt::CaseInsensitive)){
        qDebug() << "switch second";
        rmw_switchForm(2);
        //this->ui->stackedWidget->setCurrentWidget(psecondform);
    }else {
        qDebug() << "switch homepage";
        rmw_switchForm(0);
        //this->ui->stackedWidget->setCurrentWidget(phomepage);
    }
}

