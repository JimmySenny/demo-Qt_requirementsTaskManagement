/***************************************************************************
  * Description:    自定义的组件 布置在棋盘右侧  显示相关的信息
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTimerEvent>

/*
 * 侧边栏的类  包含了要实现的基本功能
 */
class SideBar : public QWidget
{
	Q_OBJECT
public:
	explicit SideBar(QWidget *parent = 0);

    //涉及到计时功能 需重定义时间事件
	void		timerEvent (QTimerEvent *);

    //重置此组件中相关变量的值
	void		SideBarReSet();

    //交替切换两边的头像
	void		turn2blackpix ();
	void		turn2redpix ();

    //有关计时的变量
	int		    timerId_start;
	int 		timerId_r;
	int		    timerId_b;

	int		    time_r_lost;
	int 		time_b_lost;

    //组件中的相关控件
	QLabel *    label_bp;
	QLabel *    label_rp;
	QPixmap *   pixmap_b;
	QPixmap *   pixmap_r;
	QLabel *    timer_label_b;
	QLabel *    timer_label_r;
	QPushButton * btn_start;
	QPushButton * btn_b;
	QPushButton * btn_r;

    //标志当前的模式  BASIC_MODE为正常 TIMER_MODE为计时 此标识为静态变量  
	static	int	timeMode_flag;

signals:
    //开始游戏按钮按下发送的信号 使棋盘组件激活 开始走棋対奕
	void		signal_sidebar_start ();
    //若有一方超时  则发出此信号 并将超时方发送出去
	void		signal_timer_over (int);
public slots:
    //开始游戏按钮按下的槽函数
	void		slot_btn_start ();
    //若是计时模式 则此2个按钮用于暂停计时
	void		slot_btn_r ();
	void		slot_btn_b ();
};


#endif // SIDEBAR_H
