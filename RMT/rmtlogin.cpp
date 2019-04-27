#include "rmtlogin.h"
#include "ui_rmtlogin.h"

RmtLogin::RmtLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RmtLogin)
{
    ui->setupUi(this);    
    msg = new RmtMessageBox();

    if( !login_init() ){
        emit signal_login_chk_err(ERR_SYS);
    }

    if( !login_init_conf()){
        emit signal_login_chk_err(ERR_CONF);

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

    //strcpy(conf_file, "C:\\Users\\Public\\rmtconf.ini");
    //QDebug("%s", conf_file);

    qDebug() << "DocumentsLocation: " << QStandardPaths::displayName(QStandardPaths::DocumentsLocation);
    //path = new QStandardPaths::QStandardPaths();
    //QMessageBox::critical(0, QObject::tr("tst"),
    //QStandardPaths::displayName(QStandardPaths::DocumentsLocation), QMessageBox::Cancel);

    QFile file( "./RmtConf.ini" );

    if ( file.exists("./RmtConf.ini") ){
        emit this->signal_login_chk_err(ERR_CONF_NOTFUND);
    }else{
        qDebug() << "RmtConf.ini 存在";
    }

    qDebug() << "RmtConf";
    /*
    QString qstrname = RmtConf().GetConf("user","name").toString();
    qDebug() << qstrname;
    QString qstrpasswd = RmtConf().GetConf("user","password").toString();
    qDebug() << qstrpasswd;
    */

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

    qDebug()<< str_user;

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
