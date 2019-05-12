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

    this->conf_value = new RmtConfValue();
    this->conf_value->getRmtConfValue();
    this->db->getInstance();
    return true;
}

void RmtmwReqInputForm::slot_on_pushButton_commit_clicked(){
    qDebug() << "on_pushButton_commit_clicked";
    if( !this->db->query_reqinput("111", "111", this->ui->dateEdit_inputdt->text()) ){
        emit this->signal_login_chk_err(APPERR_INPUT);
        this->msg->show();
    }
}
