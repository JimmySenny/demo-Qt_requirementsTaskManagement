/***************************************************************************
  * Description:    对中国象棋游戏主窗体的实现
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "mainwindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QIODevice>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "dialogaboutcchess.h"
#include "basedefine.h"
#include "loadandsave.h"
#include <iostream>

using	namespace std;

/*
 * 构造函数  首先要构造出窗体和其中的主要控件
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF_8"));//支持中文
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");//"System"

	creatMenus ();//调用创建菜单栏子函数
	creatToolBar ();//调用创建工具栏子函数

	center = new Center(this);
	this->setCentralWidget (center);
	this->center->chess->setEnabled (false);

	str_def = new	StringDefine;

	this->statusBar ()->showMessage (QString("%1\t\t\t\t%2"). \
					 arg (this->str_def->str_tile_name).arg (this->str_def->str_waitstart));

	this->setWindowIcon (QIcon(":/windowIcon.png")); //设置在任务栏的图标
        this->setWindowTitle (this->str_def->str_tile_name);	//设置主窗口标题
        this->resize (600, 600);
        this->setMaximumSize (685, 625);

	/*
	size_cface	 	= sizeof(*this->center->chess->cface);
	size_center 	= sizeof(*this->center);
	size_chess	 	= sizeof(*this->center->chess);
	size_sidebar 	= sizeof(*this->center->sidebar);
	size_cundo	= sizeof(*this->center->chess->cundo);
	savedata_buffer = (char*)calloc (size_center + size_chess + size_sidebar + size_cface + size_cundo, 1);

	savedata_buffer = (char*)malloc(size_center);
	memset (savedata_buffer, 0, size_center);
	qDebug ()<<"constructor---------savedata_buffer: "<<savedata_buffer<<"  &"<<&savedata_buffer<<"   *"<<*savedata_buffer;
	qDebug ()<<"constructor---------cface: "<<this->center->chess->cface<<"    &"<<&this->center->chess->cface;
	*/

    //连接相关的按键按下信号和相关的处理槽
	//帮助菜单
	//连接关于中国象棋的按下信号和相应的槽函数
	connect (mh_action_chinesechess, SIGNAL(triggered()),
		 this, SLOT(slot_mh_action_chinesechess()));
	//连接关于本软件的按下信号和相应的槽函数
	connect (mh_action_about, SIGNAL(triggered()),
		 this, SLOT(slot_mh_action_about()));

	//游戏设置菜单
	//按下设置悔棋步数按钮的信号与槽
	connect (ms_action_setundostep, SIGNAL(triggered()),
		 this, SLOT(slot_ms_action_setundostep()));
	//设置模式
	connect (ms_action_modetoolbarbasic, SIGNAL(triggered()),
		 this, SLOT(slot_ms_action_modebasic()));
	connect (ms_action_modetoolbartime, SIGNAL(triggered()),
		 this, SLOT(slot_ms_action_modetime()));
	//设置控制方式
	connect (ms_action_controltoolbardrag, SIGNAL(triggered()),
		 this, SLOT(slot_ms_action_controldrag()));
	connect (ms_action_controltoolbarselect, SIGNAL(triggered()),
		 this, SLOT(slot_ms_action_controlselect()));

	//游戏选项菜单
	//连接新游戏的槽函数
	connect (mg_action_newgame, SIGNAL(triggered()),
		 this, SLOT(slot_action_newgame ()));
	connect (t_action_newgame, SIGNAL(triggered()),
		 this, SLOT(slot_action_newgame ()));
	//连接悔棋使能的信号与槽函数
	connect (center->chess, SIGNAL(signal_action_undo_enable(int)),
		 this, SLOT(slot_action_undo_enable(int)));
	connect (this, SIGNAL(signal_action_undo_enable(int)),
		 this, SLOT(slot_action_undo_enable(int)));
	//连接悔棋按钮按下的信号和槽
	connect (mg_action_undo, SIGNAL(triggered()),
		 this, SLOT(slot_action_undo_triggered()));
	connect (t_action_undo, SIGNAL(triggered()),
		 this, SLOT(slot_action_undo_triggered()));
	//连接和棋按钮按下的信号和槽
	connect (mg_action_draw, SIGNAL(triggered()),
		 this, SLOT(slot_action_draw()));
	connect (t_action_draw, SIGNAL(triggered()),
		 this, SLOT(slot_action_draw()));
    /*
	//连接载入游戏的信号和槽
	connect (mg_action_loadgame, SIGNAL(triggered()),
		 this, SLOT(slot_mg_action_loadgame()));
	//连接保存游戏的信号和槽
	connect (mg_action_savegame, SIGNAL(triggered()),
		 this, SLOT(slot_mg_action_savegame()));
         */
	//退出信号和系统自带的槽函数相连
	connect (mg_action_quit, SIGNAL(triggered()),
		 this, SLOT(close()));
	connect (t_action_quit, SIGNAL(triggered()),
		 this, SLOT(close()));

	//其他
    //棋步信息状态栏显示的连接
	connect (center->chess, SIGNAL(signal_chessproc_status(int,ChessIJ,ChessIJ, int)),
		 this, SLOT(slot_chessproc_status(int,ChessIJ,ChessIJ, int)));
    //将军信息状态栏显示的连接 
	connect (center->chess, SIGNAL(signal_chesscheck()),
		 this, SLOT(slot_chesscheck()));
    //获胜弹窗弹出的连接
	connect (center->chess, SIGNAL(signal_gameover(int)),
		 this, SLOT(slot_gameover(int)));
    //超时的处理槽连接
	connect (center->sidebar, SIGNAL(signal_timer_over(int)),
		 this, SLOT(slot_timerover(int)));
    //开始游戏的信号和槽连接
	connect (center->sidebar, SIGNAL(signal_sidebar_start()),
		 this, SLOT(slot_start_game()));
}

/*
 * 菜单栏的构造的函数  可以构造出自定义的菜单栏
 */
void		
MainWindow::creatMenus ()
{
	/* 游戏菜单 */
	menu_game = this->menuBar ()->addMenu ("游戏选项(&G)");//添加菜单
	mg_action_newgame	 = menu_game->addAction ("新游戏"); //游戏菜单下动作 新游戏
	mg_action_newgame->setIcon (QIcon(":/new.png"));
	mg_action_newgame->setShortcut (tr("ctrl+N"));	//设置快捷键为 ctrl+N
	menu_game->addSeparator ();//添加分隔线

	mg_action_undo = menu_game->addAction ("悔棋");	//添加悔棋
	mg_action_undo->setEnabled (false);	//使能无效
	mg_action_undo->setIcon (QIcon(":/undo.png"));	//添加图标
	mg_action_undo->setShortcut (tr("ctrl+U"));		//设置快捷键为 ctrl+U
	mg_action_draw = menu_game->addAction ("和棋");	//添加和棋
	mg_action_draw->setIcon (QIcon(":/draw.png"));	//添加图标
	mg_action_draw->setShortcut (tr("ctrl+D"));		//设置快捷键为 ctrl+D
	menu_game->addSeparator ();//添加分隔线

    /*
	mg_action_loadgame = menu_game->addAction ("载入游戏"); //载入游戏
	mg_action_loadgame->setIcon (QIcon(":/load.png"));
	mg_action_loadgame->setShortcut (tr("ctrl+L"));	//设置快捷键为 ctrl+L
	mg_action_savegame = menu_game->addAction ("保存游戏"); //保存游戏
	mg_action_savegame->setIcon (QIcon(":/save.png"));
	mg_action_savegame->setShortcut (tr("ctrl+S"));	//设置快捷键为 ctrl+S
	menu_game->addSeparator ();//添加分隔线
    */

	mg_action_quit	 = menu_game->addAction ("退出");	//退出游戏
	mg_action_quit->setIcon (QIcon(":/quit.png"));
	mg_action_quit->setShortcut (tr("ctrl+Q"));	//设置快捷键为 ctrl+Q

	/* 设置菜单 */
	menu_set = this->menuBar ()->addMenu ("游戏设置(&S)");

	ms_action_setundostep = menu_set->addAction ("设置悔棋步数");//悔棋步数
	ms_action_setundostep->setIcon (QIcon(":/set.png"));
	ms_action_setundostep->setShortcut (tr("ctrl+E"));	//快捷键为  ctrl+E
	menu_set->addSeparator ();//添加分隔线

	menu_modetoolbar = menu_set->addMenu ("设置游戏模式");	//设置游戏模式
	menu_modetoolbar->setIcon (QIcon(":/set.png"));
	ms_action_modetoolbarbasic = menu_modetoolbar->addAction ("设置普通模式");
	ms_action_modetoolbarbasic->setShortcut (tr("ctrl+B"));	//设置快捷键为ctrl+B
	ms_action_modetoolbarbasic->setEnabled (false);//初始不可选
	ms_action_modetoolbartime = menu_modetoolbar->addAction ("设置计时模式");
	ms_action_modetoolbartime->setShortcut (tr("ctrl+T"));	//设置快捷键为ctrl+T

	menu_controltoolbar = menu_set->addMenu ("设置控制方式");	//设置控制方式
	menu_controltoolbar->setIcon (QIcon(":/set.png"));
	ms_action_controltoolbardrag = menu_controltoolbar->addAction ("设置为拖动方式");//默认方式
	ms_action_controltoolbardrag->setShortcut (tr("ctrl+G"));//快捷键为ctrl+G
	ms_action_controltoolbardrag->setEnabled (false);//初始不可选
	ms_action_controltoolbarselect = menu_controltoolbar->addAction ("设置点放方式");
	ms_action_controltoolbarselect->setShortcut (tr("ctrl+P"));//快捷键为ctrl+P


	/* 帮助菜单 */
	menu_help = this->menuBar ()->addMenu ("帮助(&H)");
	mh_action_chinesechess = menu_help->addAction ("关于中国象棋");
	mh_action_chinesechess->setIcon (QIcon(":/aboutcchess.png"));
	mh_action_about = menu_help->addAction ("关于本软件");
	mh_action_about->setIcon (QIcon(":/about.png"));
}

/*
 * 构造工具栏
 */
void		
MainWindow::creatToolBar ()
{
	toolbar = new QToolBar(this);
	toolbar->setMovable (false);//设置工具栏不可移动
	toolbar->setFloatable (false);//设置工具栏不可漂浮

	t_action_newgame = toolbar->addAction ("新游戏");	//开始游戏
	//t_action_newgame->setIcon (QIcon(":/new.png"));//设置新游戏的图标
	//t_action_newgame->setStatusTip (tr("新游戏"));
	menu_game->addSeparator ();//添加分隔线
	t_action_undo = toolbar->addAction ("悔棋");	//悔棋
	t_action_undo->setEnabled (false);
	//t_action_undo->setIcon (QIcon(":/undo.png")); //设置悔棋的图标
	menu_game->addSeparator ();//添加分隔线
	t_action_draw= toolbar->addAction ("和棋");	//和棋
	//t_action_draw->setIcon (QIcon(":/pace.png"));	//设置和棋的图标
	menu_game->addSeparator ();//添加分隔线
	t_action_quit = toolbar->addAction ("退出");	//退出
	//t_action_quit->setIcon (QIcon(":/quit.png"));	//设置退出的图标

	this->addToolBar (toolbar);
}

/*
 * 点击菜单栏关于中国象棋游戏的槽函数
 */
void		
MainWindow::slot_mh_action_chinesechess ()
{
	DialogAboutCChess aboutcchess;
	aboutcchess.exec ();
}

/*
 * 点击关于本软件的中国象棋游戏的槽函数
 */
void		
MainWindow::slot_mh_action_about ()
{
	QMessageBox::information (this, "关于本软件", this->str_def->str_about, QMessageBox::Ok);
}

/*
 * 处理按下设置悔棋步数的槽函数
 */
void		
MainWindow::slot_ms_action_setundostep ()
{
	setundosetp = new DialogSetUndostep(this);
	setundosetp->show ();
	connect (setundosetp, SIGNAL(signal_undostep(int)), this, SLOT(slot_setundostep(int)));
	this->statusBar ()->showMessage ("设置悔棋步数");
}

/*
 * 设置好多少次悔棋步数 对相应的变量赋值
 */
void		
MainWindow::slot_setundostep (int step)
{
	this->center->chess->cundo->UndoStep_set = step;
	if(step < this->center->chess->cundo->UndoStep)
		this->center->chess->cundo->UndoStep = step;
	this->center->chess->canclick = true;
}

/*
 * 设置模式为基本模式后的槽函数
 */
void		
MainWindow::slot_ms_action_modebasic ()
{
	ms_action_modetoolbarbasic->setEnabled (false);//按下后不弹起
	ms_action_modetoolbartime->setEnabled (true);//弹起
	this->center->chess->setEnabled (false);

	this->center->sidebar->timeMode_flag = BASIC_MODE;
	this->center->sidebar->SideBarReSet ();
	this->statusBar ()->showMessage ("选择基本模式");
}

/*
 * 设置模式为计时模式后的槽函数
 */
void		
MainWindow::slot_ms_action_modetime ()
{
	ms_action_modetoolbartime->setEnabled (false);//不弹起
	ms_action_modetoolbarbasic->setEnabled (true);//弹起
	this->center->chess->setEnabled (false); //棋盘不可点

	this->center->sidebar->timeMode_flag = TIMER_MODE;
	this->center->sidebar->SideBarReSet ();
	this->statusBar ()->showMessage ("选择计时模式");
}

/*
 *按下设置为拖放方式的槽
 */
void		MainWindow::slot_ms_action_controldrag ()
{
	this->ms_action_controltoolbardrag->setEnabled (false);
	this->ms_action_controltoolbarselect->setEnabled (true);
	this->center->chess->cface->controlMODE_flag = DRAG_CONTROL_MODE;
	this->statusBar ()->showMessage ("选择控制方式为拖放模式");
}
/*
 *按下设置为点放方式的槽
 */
void		MainWindow::slot_ms_action_controlselect ()
{
	this->ms_action_controltoolbarselect->setEnabled (false);
	this->ms_action_controltoolbardrag->setEnabled (true);
	this->center->chess->cface->controlMODE_flag = SELECT_CONTROL_MODE;
	this->statusBar ()->showMessage ("选择控制方式为点放模式");
}
/*
 * 点击新游戏的槽函数
 */
void		
MainWindow::slot_action_newgame ()	//新游戏的槽函数
{
	this->center->sidebar->SideBarReSet ();
	this->center->chess->ChessReSet ();
	this->center->chess->update ();
	this->center->chess->setEnabled (false);
	this->statusBar ()->showMessage ("新游戏");
}

/*
 * 点击悔棋按钮的槽函数的处理
 */
void		
MainWindow::slot_action_undo_triggered ()
{
	int ustep = center->chess->cundo->UndoStep;
	if(ustep > 0)
	{
		this->center->chess->cundo->ChessUndoPop (*center->chess->uface);
		*this->center->chess->cface = *center->chess->uface;
		this->center->chess->update ();
        this->statusBar ()->showMessage ("悔棋");
		//this->center->chess->cface->step_counter--;
		if(this->center->chess->clicks)
			this->center->chess->clicks = 0;
		else
			this->center->chess->clicks = 1;
    }
	ustep = center->chess->cundo->UndoStep;
    //将剩余的可悔棋的步数发送到使能槽函数 对悔棋按钮是否可点进行处理
	emit		signal_action_undo_enable (ustep);
    this->center->slot_turnSide (this->center->chess->cface->side);
}

/*
 * 接收悔棋使能的信号 当可悔棋的步数等于 0 时 使能为假 
 */
void		
MainWindow::slot_action_undo_enable (int ustep)//接收悔棋按钮使能的信号的槽
{
	if(ustep > 0)
	{
		mg_action_undo->setEnabled (true);
		t_action_undo->setEnabled (true);
	}
	else
	{
		mg_action_undo->setEnabled (false);
		t_action_undo->setEnabled (false);
	}
}

/*
 * 处理点击和棋的槽函数
 */
void		
MainWindow::slot_action_draw ()//和棋的槽函数
{
	if(RED == this->center->chess->cface->side)
	{
		askdrawbox = new DialogAskDraw(RED, this);
		this->statusBar ()->showMessage ("红方求和");
	}
	if(BLACK == this->center->chess->cface->side)
	{
		askdrawbox = new DialogAskDraw(BLACK, this);
		this->statusBar ()->showMessage ("黑方求和");
	}
	askdrawbox->show ();
	connect (askdrawbox, SIGNAL(signal_draw_resp(int)), this, SLOT(slot_after_draw(int)));
}

/*
 * 对和棋的选择结果处理  当同意时 显示和棋弹窗 拒绝时 显示对方胜利
 */
void		
MainWindow::slot_after_draw (int resp)
{
	if(True == resp)//同意
	{
		winnerbox = new WinnerBox(this->str_def->str_draw, this);
	}
	if(False == resp)//拒绝
	{
		if(RED == this->center->chess->cface->side)//当前是红方求和 则黑方胜利
			winnerbox = new WinnerBox(this->str_def->str_black_win, this);
		else//当前是黑方求和	则红方胜利
			winnerbox = new WinnerBox(this->str_def->str_red_win, this);
	}
	winnerbox->show ();
    
    //连接相关的槽函数
	connect (winnerbox, SIGNAL(signal_winnerbox_quit()), this, SLOT(slot_winnerbox_quit_clicked()));
	connect (winnerbox, SIGNAL(signal_winnerbox_restart()), this, SLOT(slot_action_newgame()));
}

/*
 * 对当前游戏载入的槽函数
 */
/*
void		
MainWindow::slot_mg_action_loadgame ()
{
	QString filename = QFileDialog::getOpenFileName ( this,	//父控件
							  "载入游戏",		//标题
							  "/home",			//默认路径
							  tr("Text files (*.txt)"));//过滤器
	qDebug ()<<"load: filename"<<filename;
	QByteArray con = filename.toAscii ();
	const char	*file_name = con;

	memset (savedata_buffer, 0, size_cface);
	qDebug ()<<"load: savedata_buffer: "<<savedata_buffer<<"&savedata"<<&savedata_buffer<<" *"<<*savedata_buffer;
	LoadAndSave load;
	if(load.loadfromfile (file_name, savedata_buffer))
		QMessageBox::information (this, "警告", "载入失败！", QMessageBox::Ok);
	else
	{
		qDebug ()<<"after: load: savedata_buffer: "<<savedata_buffer<<"&savedata"<<&savedata_buffer<<" *"<<*savedata_buffer;
		qDebug ()<<"load: cface: "<<this->center->chess->cface<<"  &cface"<<&this->center->chess->cface;

		//delete		this->center->chess->cface;
		//this->center->chess->cface = new ChessFace;
		//memset (this->center->chess->cface, 0, size_cface);
		//this->center->chess->update ();

		memcpy (this->center->chess->cface, savedata_buffer, size_center);
		this->center->chess->update ();
		qDebug ()<<"test***************************************test";
		qDebug ()<<"load: after_cface"<<this->center->chess->cface<<"    &cface"<<&this->center->chess->cface;
	}
}
*/

/*
 * 对保存游戏的槽函数
 */
/*
void		
MainWindow::slot_mg_action_savegame ()
{
	qDebug ()<<"memset";
	//memset (savedata_buffer, 0, size_cface);
	//memcpy (savedata_buffer, (char*)(this->center->chess->cface), size_cface);
	memset (savedata_buffer, 0, size_center);
	memcpy (savedata_buffer, (char*)(this->center), size_center);
	qDebug ()<<"save: savedata: "<<savedata_buffer<<"&savedata"<<&savedata_buffer<<" *"<<*savedata_buffer;

	LoadAndSave save;
	if(save.savetofile ("./save.txt", savedata_buffer, size_center)) //+ sizeof(void*));
	{
		QMessageBox::information (this, "警告", "保存失败！", QMessageBox::Ok);
	}
	else
		QMessageBox::information (this, "提示", "保存成功！", QMessageBox::Ok);
	qDebug ()<<"after save: savedata: "<<savedata_buffer<<"&savedata"<<&savedata_buffer<<" *"<<*savedata_buffer;
}

*/

/* 以下时在状态栏显示相应信息的槽 */

/*
 * 显示新游戏的槽
 */
void		
MainWindow::slot_start_game ()
{
	this->statusBar ()->showMessage (this->str_def->str_start);
}

/*
 * 显示将军的槽
 */
void		
MainWindow::slot_chesscheck ()
{
	this->statusBar ()->showMessage (this->str_def->str_check);
}

/*
 * 显示走棋棋步的槽
 */
void		
MainWindow::slot_chessproc_status (int chessid, \
            ChessIJ srcij, ChessIJ  desij, int flag)
{
	int	src_i = srcij.Chessi;
	int	src_j = srcij.Chessj;
	int	des_i = desij.Chessi;
	int	des_j = desij.Chessj;

	int	move_i = des_i - src_i;
	int	from = -1;
	QString		go;
	int	to = -1;

	if(NO_CHESSMAN == chessid)
	{
		this->statusBar ()->showMessage (this->str_def->str_no_cman);
	}
	else
	{
		if(False == flag)//不符合规则
		{
			if(chessid < 10)
				this->statusBar ()->showMessage (QString("%1\t        \t%2"). \
							     arg(this->str_def->str_no_rule).arg ("红方走棋"));
			else
				this->statusBar ()->showMessage (QString("%1\t        \t%2"). \
							     arg(this->str_def->str_no_rule).arg ("黑方走棋"));

		}
		else//符合规则
		{
			const	char	 * chessman[8] = {"象棋","将", "士", "相", "马", "车", "炮", "兵 "};
			switch(chessid)
			{
				//红棋的士 相 马
				case		R_S:
				case		R_X:
				case		R_M:
					if(move_i > 0)
						go = "退";
					else
						go = "进";
					from = abs (9 - src_j);
					to = abs (9 - des_j);
					break;
				case		R_K:
				case		R_J:
				case		R_P:
				case		R_B:
					if(0 != move_i)
					{
						if(move_i > 0)
							go = "退";
						else
							go = "进";
						from = abs(9 - src_j);
						to = abs (move_i);
					}
					else
					{
						go = "平";
						from = abs (9 - src_j);
						to = abs (9 - des_j );
					}
					break;
				case		B_S:
				case		B_X:
				case		B_M:
					if(move_i > 0)
						go = "进";
					else
						go = "退";
					from = abs (src_j + 1);
					to = abs (des_j + 1);
					break;
				case		B_K:
				case		B_J:
				case		B_P:
				case		B_Z:
					if(0 != move_i)
					{
						if(move_i > 0)
							go = "进";
						else
							go = "退";
						from = src_j + 1;
						to = abs (move_i);
					}
					else
					{
						go = "平";
						from = src_j + 1;
						to = abs (des_j + 1);
					}
					break;
				default:
					break;
			}//switch
			if(chessid < 10)
			{
				const	char * chinese_num[10] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
				this->statusBar ()->showMessage (QString("%1 %2 %3 %4\t        \t%5"). \
								 arg (chessman[chessid]).arg (chinese_num[from]).arg (go).arg (chinese_num[to]). \
									arg(this->str_def->str_black_go));
			}
			else
			{
				chessid -= 10;
				this->statusBar ()->showMessage (QString("%1 %2 %3 %4\t        \t%5"). \
						 arg (chessman[chessid]).arg (from).arg (go).arg (to). \
								arg(this->str_def->str_red_go));
			}
		}//else  符合规则
	}//if  有棋走
}

/*
 * 显示超时的信息在状态栏显示
 */
void		
MainWindow::slot_timerover (int side)
{
	if(RED == side)
	{
		this->statusBar ()->showMessage ("红方超时！");
		this->slot_gameover (BLACK);
	}
	if(BLACK == side)
	{
		this->statusBar ()->showMessage ("黑方超时！");
		this->slot_gameover (RED);
	}
}

/*
 * 显示游戏获胜方的信息在状态栏显示
 */
void		
MainWindow::slot_gameover (int side)
{
	this->center->chess->setEnabled (false);
	if(RED == side)
	{
		this->statusBar ()->showMessage (this->str_def->str_red_win);
		winnerbox = new WinnerBox(this->str_def->str_red_win, this);
	}
	if(BLACK == side)
	{
		this->statusBar ()->showMessage (this->str_def->str_black_win);
		winnerbox = new WinnerBox(this->str_def->str_black_win, this);
	}
	winnerbox->show ();
	connect (winnerbox, SIGNAL(signal_winnerbox_quit()), this, SLOT(slot_winnerbox_quit_clicked()));
	connect (winnerbox, SIGNAL(signal_winnerbox_restart()), this, SLOT(slot_action_newgame()));
}

/*
 * 游戏有胜方后 若选择退出游戏 则主窗体关闭
 */
void		
MainWindow::slot_winnerbox_quit_clicked ()
{
	this->close ();
}

MainWindow::~MainWindow()
{
}
