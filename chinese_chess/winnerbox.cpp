/***************************************************************************
  * Description:    对获胜方的弹窗的实现
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "winnerbox.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

/*
 * 构造函数
 */
WinnerBox::WinnerBox(QString str, QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(str, this);
    label->setFont (QFont("微软雅黑", 16, QFont::Bold));

    btn_restart = new QPushButton("重来一局", this);
    btn_quit = new QPushButton("退出纷争", this);
    QHBoxLayout * horlayout = new QHBoxLayout;
    horlayout->addWidget (btn_restart, 0, Qt::AlignHCenter);
    horlayout->addWidget (btn_quit, 0, Qt::AlignHCenter);

    QVBoxLayout * mainlayout = new QVBoxLayout;
    mainlayout->addWidget (label, 0, Qt::AlignCenter);
    mainlayout->addLayout (horlayout);

    this->setLayout (mainlayout);
    this->setWindowTitle ("楚汉之争 胜负已分");
    this->resize (320, 160);

    connect (btn_restart, SIGNAL(clicked()), this, SLOT(slot_winnerbox_restart()));
    connect (btn_quit, SIGNAL(clicked()), this, SLOT(slot_winnerbox_quit()));
}

/*
 * 退出游戏的选择
 */
void		
WinnerBox::slot_winnerbox_quit ()
{
    emit 	signal_winnerbox_quit ();
    //usleep(1000);
    this->close ();
}

/*
 * 重置游戏的选择
 */
void		
WinnerBox::slot_winnerbox_restart ()
{
    emit		signal_winnerbox_restart ();
    //usleep(1000);
    this->close ();
}
