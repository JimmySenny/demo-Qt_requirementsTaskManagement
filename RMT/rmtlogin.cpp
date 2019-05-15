#include "rmtlogin.h"
#include "ui_rmtlogin.h"

RmtLogin::RmtLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtLogin)
{
    ui->setupUi(this);

    this->confins = RmtConfValue::getInstance();
    //qDebug() <<"RmtLogin"<< (*confins->conf );
    this->dbins = DbMysql::getInstance();
    this->msg = new RmtMessageBox();
    connect(this,SIGNAL(signal_login_chk_err(int)),\
            msg,SLOT(slot_msgbox_set_code(int)));


    if( !login_init() ){
        emit signal_login_chk_err(ERR_SYS);
        this->msg->show();
        this->close();
    }

    if( !login_init_conf()){
        emit signal_login_chk_err(ERR_CONF);
        this->msg->show();
        this->close();
        return;
    }



    connect(this->ui->pushButton_login, SIGNAL(clicked()), \
            this,SLOT(slot_login_pbuttonlogin_to_mainwindow()));
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

    /*
    if ( !this->confins->getRmtConfValue()){
        emit signal_login_chk_err(ERR_CONF_NOTFUND);
        this->msg->show();
        qDebug() << "配置文件不存在";
        return false;
    }
    */
    if ( !this->dbins->db_init() ){
        emit signal_login_chk_err(ERR_DBINIT);
        this->msg->show();
        qDebug() << "数据库连接初始化错误";
        return  false;
    }

    return true;
}

bool
RmtLogin::login_init_conf(){
//    qDebug() << "DocumentsLocation: " << QStandardPaths::displayName(QStandardPaths::DocumentsLocation);

    this->ui->lineEdit_name->setText(*this->confins->user_id);
    this->ui->lineEdit_pwd->setText(*this->confins->user_pwd);
    this->ui->lineEdit_pwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    qDebug() << this->ui->lineEdit_pwd->text();

    return true;

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

  qDebug() << "chk_user_pwd()" << str_user << str_pwd;

  if( !dbins->query_chkuser(str_user,str_pwd)){
      qDebug()<< "认证失败";
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
        emit this->signal_login_chk_err(APPERR_INPUT);
        this->msg->show();
        return;
  }

  if(!chk_user_pwd()){
      this->ui->lineEdit_pwd->clear();
      this->ui->lineEdit_pwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        emit this->signal_login_chk_err(APPERR_LOGIN);
        this->msg->show();
        qDebug()<< "chk_user_pwd()";
        return;
  }

    qDebug()<< "登录成功";
    *confins->user_id = this->ui->lineEdit_name->text();
    *confins->user_pwd = this->ui->lineEdit_pwd->text();
    this->confins->setRmtConfValue(confins);

    RmtMainWindow * rmtmainwindow = new RmtMainWindow();
    rmtmainwindow->show();
    this->close();
}
