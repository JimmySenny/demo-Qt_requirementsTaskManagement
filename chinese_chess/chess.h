/***************************************************************************
  * Description:    象棋抽象的类  完成棋盘绘制  并将棋盘和棋局相关对象整合到一起 
  * Author  : As_ming
  * Language: c/c++/Qt
  * Features: 
  * Revision: 
  * Date    : 2012-05-06
  ***************************************************************************/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "basedefine.h"
#include "chessface.h"
#include "chessundo.h"

/*
 * 象棋类   通过实例话出棋局 悔棋棋局  等对象  实现基本的象棋走棋功能
 * 成员对象：
 * <1>棋局类 
 * <2>悔棋类
 * <3>键值对类  包括鼠标点击位置的对象 松开位置的对象 松开位置的对象
 * 成员函数：
 * <1>重定义的绘图事件  绘制棋盘和和根据棋子对象绘制棋子
 * <2>重定义的鼠标事件  处理鼠标事件
 * <3>棋盘重置函数  完成棋盘相关所有对象的数据重置
 * <4>其他相应的信号和槽函数 用于内部事件的通信及和上层外部组件之间的通信
 */
class Chess : public QWidget
{
    Q_OBJECT
public:
    explicit Chess(QWidget *parent = 0);

    void		ChessReSet ();
	//根据选择的棋子的起始和目标位置 完成流程控制
	void		ChessMoveCMan (ChessIJ	  src, ChessIJ	 dest);

    bool		mousePress;	    //若左键按下则为1 否则为0
    bool		mouseRelease;   //若左键松开则为0 否则为1
	bool		canclick;		//可以移动 则为1 否则为0

    //当前棋局类
    ChessFace * cface;
    //临时存储当前棋局之前一步的棋局
    ChessFace * uface;
    //键值对类 保存鼠标操作的相关信息
    ChessIJ     pressij;
    ChessIJ     releaseij;
    ChessIJ     moveij;
	ChessIJ		selectij;
	ChessIJ		placeij;

    //悔棋类
    ChessUndo * cundo;

	int		clicks;

signals:
    //内部通信
    //发送鼠标事件中点击的位置 
    void		signal_mouseEvent_p (int, int);
    //发送鼠标事件中释放的位置
    void		signal_mouseEvent_r (int, int);
    //发送鼠标事件中移动的位置
    void		signal_mouseEvent_m (int, int);

    //向外部发送
    //发送将军的信号
	void		signal_chesscheck ();
    //发送游戏结束的信号
    void		signal_gameover (int);
    //发出使得悔棋按钮使能的信号
    void		signal_action_undo_enable(int);	
    //发出轮到那方走棋的信号
	void		signal_turnSide (int);
    //发送当前下棋的相关状态
    //当前走棋状态 选择的棋子 走棋的源位置 目标位置
    void		signal_chessproc_status (int, ChessIJ, ChessIJ, int);	
public slots:
    //内部槽
    //接收鼠标事件相关的槽
    void		slot_mouseEvent_p (int, int);
    void		slot_mouseEvent_r (int, int);
    void		slot_mouseEvent_m (int, int);

protected:
    //绘图事件重定义
    void		paintEvent (QPaintEvent *);	
    //鼠标点击事件重定义
    void		mousePressEvent (QMouseEvent *); 
    //鼠标松开重定义
    void		mouseReleaseEvent (QMouseEvent *); 
    //鼠标移动重定义
    void		mouseMoveEvent (QMouseEvent *);	
};

#endif // CHESSBOARD_H
