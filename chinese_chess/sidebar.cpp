/***************************************************************************
  * Description:    实现自定义的侧边栏
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "sidebar.h"
#include "basedefine.h"
#include <QVBoxLayout>
#include <QDebug>

//静态变量存游戏模式  避免新游戏的开始使得模式改变
int	SideBar::timeMode_flag = 0;

SideBar::SideBar(QWidget *parent) :
    QWidget(parent)
{
    //头像
    pixmap_b = new QPixmap;
    pixmap_b->load (":/blackside.png")	;
    label_bp = new QLabel(this);
    label_bp->setPixmap (*pixmap_b);

	pixmap_r = new QPixmap;
    pixmap_r->load (":/redside.png");
    label_rp = new QLabel(this);
    label_rp->setPixmap (*pixmap_r);

    //时间标签
    timer_label_b = new QLabel(this);  //显示黑方时间标签
    timer_label_b->setSizePolicy(QSizePolicy::Ignored,
				QSizePolicy::Ignored);
    //time_label_b->setFont(QFont("Times",18,QFont::Bold));
    QPalette palette_b;
    palette_b.setColor(QPalette::WindowText,Qt::black);
    timer_label_b->setPalette(palette_b);

    timer_label_r = new QLabel(this);  //显示红方时间标签
    timer_label_r->setSizePolicy(QSizePolicy::Ignored,
				QSizePolicy::Ignored);
    //time_label_r->setFont(QFont("Times",18,QFont::Bold));
    QPalette palette_r;
    palette_r.setColor(QPalette::WindowText,Qt::red);
    timer_label_r->setPalette(palette_r);

    //暂停按钮
    btn_b = new QPushButton(this);
	btn_b->setIcon (QIcon(":/btn_pause.ico"));
    btn_b->setEnabled (false);
    btn_r = new QPushButton(this);
	btn_r->setIcon (QIcon(":/btn_pause.ico"));
    btn_r->setEnabled (false);

    btn_start = new QPushButton("开始游戏", this);

    QVBoxLayout * verlayout = new QVBoxLayout;
    verlayout->addWidget (label_bp, 0, Qt::AlignCenter);
    verlayout->addWidget (btn_b, 0, Qt::AlignCenter);
    verlayout->addWidget (timer_label_b, 0, Qt::AlignCenter);
    verlayout->addWidget (btn_start, 0, Qt::AlignCenter);
    verlayout->addWidget (timer_label_r, 0, Qt::AlignCenter);
    verlayout->addWidget (btn_r, 0, Qt::AlignCenter);
    verlayout->addWidget (label_rp, 0, Qt::AlignCenter);

    this->setLayout (verlayout);

    //相关变量的初始化
    timerId_start = -1;
    timerId_r = -1;
    timerId_b = -1;

    time_r_lost = 0;
    time_b_lost = 0;

	connect (btn_start, SIGNAL(clicked()), this, SLOT(slot_btn_start()));
	connect (btn_r, SIGNAL(clicked()), this, SLOT(slot_btn_r()));
	connect (btn_b, SIGNAL(clicked()), this, SLOT(slot_btn_b()));
}

/*
 * 重置此组件中相关变量的值
 */
void		
SideBar::SideBarReSet ()
{
	timerId_start = -1;
	timerId_r = -1;
	timerId_b = -1;

	time_r_lost = 0;
	time_b_lost = 0;

	btn_start->setEnabled (true);
	btn_r->setEnabled (false);
	btn_b->setEnabled (false);

	label_bp->setPixmap (*pixmap_b);
	label_rp->setPixmap (*pixmap_r);
    
    //若是计时模式 则显示时间标签  
	if(TIMER_MODE == timeMode_flag)
	{
		timer_label_b->setText(QString("Time: 00:00:00"));
		timer_label_r->setText(QString("Time: 00:00:00"));
	}
    //否则 标签中内容清空
	else
	{
		timer_label_b->clear ();
		timer_label_r->clear ();
	}
}

/*
 * 轮换头像  这是红方走棋时
 */
void		
SideBar::turn2redpix ()
{
	label_rp->setPixmap (*pixmap_r);
	label_bp->setText ("等待...");
}

/*
 * 轮换头像  这是黑方走棋时
 */
void		
SideBar::turn2blackpix ()
{
	label_bp->setPixmap (*pixmap_b);
	label_rp->setText ("等待...");
}

/*
 * 开始游戏按钮按下的槽函数
 */
void		
SideBar::slot_btn_start ()
{
	btn_start->setEnabled (false);
	label_bp->setText ("等待...");
	emit		signal_sidebar_start ();

	if(TIMER_MODE == timeMode_flag)
	{
		btn_b->setEnabled (false);
		btn_r->setEnabled (true);
		timerId_start = startTimer (1000);
	}
}

/*
 * 暂停红方时间按钮的槽函数
 */
void		
SideBar::slot_btn_r ()
{
	btn_b->setEnabled (true);
	btn_r->setEnabled (false);

	if(-1 != timerId_start)
	{
		killTimer (timerId_start);
		timerId_start = -1;
	}
	killTimer (timerId_r);
	timerId_b = startTimer(1000);
}

/*
 * 暂停黑方时间按钮的槽函数
 */
void		
SideBar::slot_btn_b ()
{
	//qDebug ()<<"timerId_b"<<timerId_b;
	btn_r->setEnabled (true);
	btn_b->setEnabled (false);

	killTimer (timerId_b);
	timerId_r = startTimer(1000);
}

/*
 * 重定义的时间事件 根据计时器  更新时间标签
 */
void		
SideBar::timerEvent (QTimerEvent * e)
{
	if((timerId_r == e->timerId ()) || (timerId_start == e->timerId ()))
	{
		time_r_lost++;
		if(time_r_lost >= MAX_TIME)
		{
			killTimer (timerId_r);
			timerId_r = -1;
			emit		signal_timer_over (RED);//红方超时
			this->timer_label_r->setText ("超时");
		}
		else
		{
		//qDebug ()<<"r_lost"<<time_r_lost;
		int hour = 0, minute = 0, second = 0;
		hour = (int)(time_r_lost/60/60);
		if(hour >= 24)
			hour = 0;
		minute = (int)((time_r_lost - hour*60*60) / 60);
		second = time_r_lost % 60;
		char temp_r[20];
		sprintf(temp_r, "Time: %02d:%02d:%02d", hour, minute, second);
		this->timer_label_r->setText(QString(temp_r));
		}
	}
	else if(timerId_b == e->timerId ())
	{
		time_b_lost++;
        if(time_b_lost >= MAX_TIME)
		{
			killTimer (timerId_b);
			emit		signal_timer_over (BLACK);//黑方超时
			this->timer_label_r->setText ("超时");
		}
		else
		{
		//qDebug ()<<"b_lost"<<time_b_lost;
		int hour = 0, minute = 0, second = 0;
		hour = (int)(time_b_lost/60/60);
		if(hour >= 24)
			hour = 0;
		minute = (int)((time_b_lost - hour*60*60) / 60);
		second = time_b_lost % 60;
		char temp_b[20];
		sprintf(temp_b, "Time: %02d:%02d:%02d", hour, minute, second);
		this->timer_label_b->setText(QString(temp_b));
		}
	}
	else
		exit(1111);
}
