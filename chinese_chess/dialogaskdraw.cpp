/***************************************************************************
  * Description:    求和确认弹窗的实现
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "dialogaskdraw.h"
#include <QGridLayout>
#include "basedefine.h"
#include "stringdefine.h"

DialogAskDraw::DialogAskDraw(int 	side, QWidget *parent) :
    QDialog(parent)
{
	StringDefine str_def;

    //如果当前时红方 则是红方求和
	if(RED == side)
		label_show = new QLabel(str_def.str_red_draw, this);
    //若时黑方  则是黑方求和  
	if(BLACK == side)
		label_show = new QLabel(str_def.str_black_draw, this);

	label_show->setFont (QFont("微软雅黑", 14, QFont::Bold));

    //按钮实现 
	btn_agree = new QPushButton("同意", this);
	btn_refuse = new QPushButton("拒绝", this);

	QGridLayout * gridlayout = new QGridLayout;
	gridlayout->addWidget (label_show, 2, 2, 2, 6);
	gridlayout->addWidget (btn_agree,  3, 3, 2, 1);
	gridlayout->addWidget (btn_refuse, 3, 5, 2, 1);

	this->setLayout (gridlayout);
	this->resize (300, 160);

    //根据不同的按钮被点下,调用不同的槽函数
	connect (btn_agree, SIGNAL(clicked()), this, SLOT(slot_btn_agree_clicked()));
	connect (btn_refuse, SIGNAL(clicked()), this, SLOT(slot_btn_refuse_clicked()));
}

/*
 * 同意发送True的信号
 */
void		DialogAskDraw::slot_btn_agree_clicked ()
{
	emit 		signal_draw_resp (True);	//同意发True
        //usleep(1000);
	this->close ();
}

/*
 * 不同意发送False的信号
 */
void		DialogAskDraw::slot_btn_refuse_clicked ()
{
	emit		signal_draw_resp (False); 	//拒绝发False
    //usleep(1000);
	this->close ();
}
