#ifndef RMTLOGIN_H
#define RMTLOGIN_H

#include <QMainWindow>

#include "rmtcomm.h"

namespace Ui {
class RmtLogin;
}

class RmtLogin : public QMainWindow
{
    Q_OBJECT

signals:
    void    signal_login_chk_err(int);
public slots:
    void	slot_login_pbuttonlogin_to_mainwindow ();
//    void	slot_login_pbuttonlogin_action_err ( int );

public:
    explicit RmtLogin(QWidget *parent = nullptr);
    ~RmtLogin();
    bool login_init();
    bool login_init_conf(); //配置文件初始化
    bool chk_input();    //校验账号密码
    bool chk_user_pwd();    //校验账号密码

    QFile * file;
    QStandardPaths *path ;

private:
    Ui::RmtLogin *ui;
    RmtMessageBox * msg;


};

#endif // RMTLOGIN_H
