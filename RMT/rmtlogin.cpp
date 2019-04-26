#include "rmtlogin.h"
#include "ui_rmtlogin.h"

RmtLogin::RmtLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtLogin)
{
    ui->setupUi(this);    
    msg = new RmtMessageBox();

    if( login_init() ){
        emit signal_login_chk_err(10000);
    }




    connect(this->ui->pushButton_login, SIGNAL(clicked()), \
            this,SLOT(slot_login_pbuttonlogin_to_mainwindow()));

    connect(this,SIGNAL(signal_login_chk_err(int)),\
            msg,SLOT(slot_msgbox_set_code(int)));

}

RmtLogin::~RmtLogin()
{
    delete ui;
}

bool
RmtLogin::login_init(){
    this->setWindowTitle("登录界面");

    this->ui->lineEdit_name->setMaxLength(16);
    this->ui->lineEdit_name->setMaxLength(16);

    return true;
}

bool
RmtLogin::login_init_conf(){

    if ( file->exists("./conf/sys.ini") ){

    }

    return 0;
}

bool
RmtLogin::chk_input(){
    if( 0 == this->ui->lineEdit_name->text().length() ||
        0 == this->ui->lineEdit_pwd->text().length() ){
        return false;
    }
    return true;
}

bool
RmtLogin::chk_user_pwd(){
    QString str_user = this->ui->lineEdit_name->text();
    QString str_pwd = this->ui->lineEdit_pwd->text();

    //TODO
    if(str_user.compare("000") || \
            str_pwd.compare("000")){
        return false;
    }
    return true;
}

/*
 * 点击登录连接逻辑处理槽函数
 */
void
RmtLogin::slot_login_pbuttonlogin_to_mainwindow ()
{
    if(!chk_input()){
        emit this->signal_login_chk_err(false);
        this->msg->show();
        return;
    }

    if(!chk_user_pwd()){
        this->ui->lineEdit_pwd->clear();
        emit this->signal_login_chk_err(2);
        this->msg->show();
        return;
    }

    RmtMainWindow * rmtmainwindow = new RmtMainWindow();
    rmtmainwindow->show();
    this->close();
    //return rmtmainwindow.exec();
}
