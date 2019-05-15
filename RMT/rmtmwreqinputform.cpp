#include "rmtmwreqinputform.h"
#include "ui_rmtmwreqinputform.h"

RmtmwReqInputForm::RmtmwReqInputForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RmtmwReqInputForm)
{
    ui->setupUi(this);
    msg = new RmtMessageBox();
    connect(this,SIGNAL(signal_login_chk_err(int)),\
            msg,SLOT(slot_msgbox_set_code(int)));

    rmw_reqinput_init();

    connect(this->ui->pushButton_commit, SIGNAL(clicked()), \
            this, SLOT(slot_on_pushButton_commit_clicked()));
}

RmtmwReqInputForm::~RmtmwReqInputForm()
{
    delete ui;
}

bool
RmtmwReqInputForm::rmw_reqinput_init(){
    qDebug() << QDate::currentDate();
    this->ui->dateEdit_inputdt->setDate(QDate::currentDate());
    this->ui->dateEdit_inputdt->setDisabled(true);
    this->ui->dateEdit_expectdt->setMinimumDate(QDate::currentDate());
    this->ui->dateEdit_expectdt->setDate(QDate::currentDate().addDays(10));

    //this->confins = RmtConfValue::getInstance();
    //this->confins->getRmtConfValue();
    this->dbins = DbMysql::getInstance();
    if ( !this->dbins->db_init() ){
        emit signal_login_chk_err(ERR_DBINIT);
        this->msg->show();
        qDebug() << "数据库连接初始化错误";
        return  false;
    }
    return true;
}

void RmtmwReqInputForm::slot_on_pushButton_commit_clicked(){
    qDebug() << "RmtmwReqInputForm::on_pushButton_commit_clicked";
    if( !this->dbins->query_reqinput("111", "111", this->ui->dateEdit_inputdt->text()) ){
        emit this->signal_login_chk_err(APPERR_INPUT);
        this->msg->show();
    }
}
