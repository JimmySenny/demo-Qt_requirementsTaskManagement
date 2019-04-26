/***************************************************************************
  * Description:    基于qt的中国象棋游戏的主窗体 在此窗体内完成対奕 设定等的操作
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QString>
#include "center.h"
#include "dialogsetundostep.h"
#include "winnerbox.h"
#include "dialogaskdraw.h"
#include "stringdefine.h"


/*
 * 中国象棋游戏窗体的类 实现游戏的功能
 * 主要由信号和槽 驱动一些功能控件的完成
 * 之前定义的类完成相关功能的实现
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    //生成菜单栏的函数
    void		creatMenus ();	
    //生成工具栏的函数
    void		creatToolBar ();	

signals:
    //发送当前悔棋按钮使能的信号
    void		signal_action_undo_enable (int);
public slots:
    //声明帮助菜单下关于中国象棋的槽函数
    void		slot_mh_action_chinesechess ();
    //声明帮助菜单下关于本软件的槽函数
    void		slot_mh_action_about ();	
    //按下设置悔棋步数的槽
    void		slot_ms_action_setundostep ();
    //接收设置好的数值的槽
    void		slot_setundostep (int);
    //接收悔棋按钮使能的信号的槽
    void		slot_action_undo_enable (int);
    //处理悔棋按钮按下的信号的槽函数
    void		slot_action_undo_triggered ();
    //按下设置为基本模式的槽
    void		slot_ms_action_modebasic ();
    //按下设置为计时模式的槽
    void		slot_ms_action_modetime ();
	//按下设置为拖放方式的槽
	void		slot_ms_action_controldrag ();
	//按下设置为点放方式的槽
	void		slot_ms_action_controlselect ();

    //新游戏的槽函数
    void		slot_action_newgame ();	
    //和棋的槽函数
    void		slot_action_draw ();
    //处理和棋后选择的槽
	void		slot_after_draw (int);

    //对当前游戏状态在任务栏显示相应信息的槽
    //显示新游戏信息
	void		slot_start_game ();
    //显示将军信息
	void		slot_chesscheck ();
    //显示棋子走棋信息
    void		slot_chessproc_status (int, ChessIJ, ChessIJ, int);

    //处理游戏结束后的槽
    void		slot_gameover (int);
	void		slot_timerover (int);
    void		slot_winnerbox_quit_clicked ();
    /*
    void		slot_mg_action_loadgame ();
    void		slot_mg_action_savegame ();
    */
private:
    //有关主窗体中显示的及内容的声明
    //中心自定义组件
    Center* center;	

    /* 游戏菜单声明 */
    QMenu	* menu_game;
    QAction	* mg_action_newgame; //游戏菜单下动作 新游戏
    QAction	* mg_action_undo;	//悔棋
    QAction	* mg_action_draw;	//和棋
    //QAction	* mg_action_loadgame; //载入游戏
    //QAction	* mg_action_savegame; //保存游戏
    QAction	* mg_action_quit;	//退出游戏
    /* 设置菜单声明 */
    QMenu	* menu_set;

    QAction	* ms_action_setundostep;//设置悔棋步数
    QMenu	* menu_modetoolbar;	//设置游戏模式的一级菜单
    QAction	* ms_action_modetoolbarbasic;	//设置普通模式
    QAction	* ms_action_modetoolbartime;	//设置计时模式
	QMenu *	menu_controltoolbar;//这是游戏走棋控制模式的一级菜单
	QAction *		ms_action_controltoolbardrag;//设置为拖动模式
	QAction *		ms_action_controltoolbarselect;//设置为选择放置模式

    /* 帮助菜单声明 */
    QMenu	* menu_help;
    QAction	* mh_action_chinesechess;	//关于中国象棋的介绍
    QAction	* mh_action_about; //关于本软件

    /* 工具栏的声明 */
    QToolBar	* toolbar;
    QAction	* t_action_newgame;	//新游戏
    QAction	* t_action_undo;	//悔棋
    QAction	* t_action_draw;	//和棋
    QAction	* t_action_quit;	//退出

	StringDefine		* str_def;

    DialogSetUndostep * setundosetp;
    WinnerBox * winnerbox;
	DialogAskDraw * askdrawbox;

    /*
	int		size_center;
	int		size_chess;
	int		size_sidebar;
	int		size_cface;
	int		size_cundo;
    char	* savedata_buffer;
    */
};

#endif // MAINWINDOW_H
