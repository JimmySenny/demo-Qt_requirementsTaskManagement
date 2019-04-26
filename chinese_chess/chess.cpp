/***************************************************************************
 * Description:    象棋类的实现
 * Author  : As_ming
 * Language: c++/Qt
 * Features: 
 * Revision: 
 * Date    : 2012-05-06
 ***************************************************************************/

#include "chess.h"
#include <QDebug>

/*
 * 构造函数 
 * 1.实现对象棋类中的类的对象的实例化
 * 2.完成相关内部信号和槽的连接
 */
Chess::Chess(QWidget *parent)
: QWidget(parent)
{
    //实例化并初始话棋局
    cface = new ChessFace;
    cface->initChessFace ();

    //临时棋局的实例化 并将最开始的棋局存入 
    uface = new ChessFace;
    *uface = *cface;

    //悔棋对象的实例化
    cundo = new ChessUndo;

    //其他标志变量的初始化
    mousePress = false;
    mouseRelease = false;
    canclick = true;
	clicks = 0;
    this->setMouseTracking (true);
    //this->setMinimumSize (XBW, YBW);
    this->setFixedSize (XBW, YBW);

    //鼠标移动事件
    connect (this, SIGNAL(signal_mouseEvent_m(int,int)),
                this, SLOT(slot_mouseEvent_m(int,int)));
    //鼠标点击事件
    connect (this, SIGNAL(signal_mouseEvent_p(int,int)),
                this, SLOT(slot_mouseEvent_p(int,int)));
}

/*
 * 棋局重置 
 */
void		
Chess::ChessReSet()
{
    cface->initChessFace ();
    cundo->initChessUndo ();
    canclick = true;
	pressij.ReSetChessIJ ();
	releaseij.ReSetChessIJ ();
	moveij.ReSetChessIJ ();
	selectij.ReSetChessIJ ();
	placeij.ReSetChessIJ ();
    emit 	signal_action_undo_enable (cundo->UndoStep);
}


/*
 * 重写的绘图事件 用于象棋盘和棋子的绘制
 */
void		
Chess::paintEvent (QPaintEvent *)
{
    //初始化QPainter 对象
    QPainter painte(this);
    //绘制棋盘
    QImage image_board;	//初始化棋盘的QImage对象
    image_board.load (":/Board.png");	//载入棋盘图片
    QRect rect_board(0, 0, XBW, YBW);//设置棋盘的位置和大小
    painte.drawImage (rect_board, image_board);//绘制棋盘

    //绘制棋子
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 9; x++)
        {
            if(cface->Chessface[y][x].Chessid != NO_CHESSMAN)
              painte.drawImage (cface->Chessface[y][x].Chessij.Chessj * BWA + SW,\
                          cface->Chessface[y][x].Chessij.Chessi * BWA + SW, \
                          cface->Chessface[y][x].Chessimage);
        }//for
    }//for

    if(mousePress)
    {
        if(DRAG_CONTROL_MODE == cface->controlMODE_flag)
        {
                QPen    pen;
                    if(RED  == cface->side)
                                pen.setColor (Qt::red);
                    if(BLACK == cface->side)
                        pen.setColor (Qt::black);
                pen.setWidth (2);
                        pen.setStyle (Qt::DashDotLine);
                        pen.setJoinStyle (Qt::RoundJoin);
                        painte.setPen (pen);
                QRect		rectselect(pressij.Chessj * BWA - 1, pressij.Chessi * BWA - 1, BWA + SW, BWA + SW);
            painte.drawEllipse (rectselect);
        }
        if(SELECT_CONTROL_MODE == cface->controlMODE_flag)
        {
	//qDebug ()<<"000000000000000000000000000000000000000000000";
                QPen    pen;
        if(RED == cface->side)
    {
                        pen.setColor (Qt::red);
	    if(((cface->step_counter) % 2 == 0) && (0 == clicks))
                        pen.setColor (Qt::black);
    }
            if(BLACK == cface->side)
        {
                        pen.setColor (Qt::black);
	    if(((cface->step_counter) % 2 == 1) && (0 == clicks))
                        pen.setColor (Qt::red);
        }


                pen.setWidth (2);
                        pen.setStyle (Qt::DashDotLine);
                        pen.setJoinStyle (Qt::RoundJoin);
                        painte.setPen (pen);
    switch(clicks)
    {
    case	0:
        {
	//qDebug ()<<"=============================================";
	//qDebug ()<<"clicks"<<clicks<<"side"<<cface->side;
	    //qDebug ()<<"counter"<<cface->step_counter;
            QRect		rectselect(placeij.Chessj * BWA - 1, placeij.Chessi * BWA -1, BWA + SW, BWA + SW);
            painte.drawEllipse (rectselect);
        }
    case	1:
        {
	//qDebug ()<<"----------------------------------------------------------------------------------";
	//qDebug ()<<"clicks"<<clicks<<"side"<<cface->side;
	    //qDebug ()<<"counter"<<cface->step_counter;
            QRect		rectselect(selectij.Chessj * BWA - 1, selectij.Chessi * BWA -1, BWA + SW, BWA + SW);
            painte.drawEllipse (rectselect);
        break;
        }
    default:
        break;
        }
    }
    }
}

/*
 * 重写的鼠标点击事件 处理点击的位置  
 */
void		
Chess::mousePressEvent (QMouseEvent * event)
{
    //若是左键点击
    if(event->button () == Qt::LeftButton)
    {
	if(DRAG_CONTROL_MODE == cface->controlMODE_flag)
        {
            //将位置转换成键值对
            pressij = cface->mouseToChessFace (event->x (), event->y ());
            //qDebug ()<<"press"<<pressij.Chessi<<pressij.Chessj<<"*****************";
            //点击位置在棋盘内有效
            if((pressij.Chessi != -1) && (pressij.Chessj != -1))
            {
                mousePress = true;  //标志已按下
                mouseRelease = false;//标志已松开
                *uface = *cface;
                //将此键值对发送出去
                emit		signal_mouseEvent_p (pressij.Chessi, pressij.Chessj);
            }
		}//if DRAG
		if(SELECT_CONTROL_MODE == cface->controlMODE_flag)
		{
			switch(clicks)
			{
                case	0:
				{
					selectij = cface->mouseToChessFace (event->x (), event->y ());
                    //qDebug ()<<"clicks = 0"<<selectij.Chessi<<","<<selectij.Chessj;
					if((selectij.Chessi != -1) && (selectij.Chessj != -1))
					{
                                mousePress = true;  //标志已按下
                        *uface = *cface;
                                emit		signal_mouseEvent_p (selectij.Chessi, selectij.Chessj);
                                clicks++;
					}
					break;
                }
                case	1:
				{
					placeij = cface->mouseToChessFace (event->x (), event->y ());
                    //qDebug ()<<"clicks = 1"<<placeij.Chessi<<","<<placeij.Chessj;
					if((placeij.Chessi != -1) && (placeij.Chessj != -1))
					{
                                mousePress = true;  //标志已按下
                        *uface = *cface;
					this->ChessMoveCMan (selectij, placeij);
                                emit		signal_mouseEvent_p (placeij.Chessi, placeij.Chessj);
                clicks = 0;
                //usleep (1000);
                    }
					break;
				}
				default:
					break;
			}//switch
		}//if SELECT
    }//if leftbutton
}

/*
 * 松开鼠标的事件的重定义
 */
void		
Chess::mouseReleaseEvent (QMouseEvent * event)
{
    //若是左键松开
    if(event->button () == Qt::LeftButton) 
    {
	if(DRAG_CONTROL_MODE == cface->controlMODE_flag)
        {
            mousePress = false;
            mouseRelease = true;
            //将位置转换成键值对
            releaseij = cface->mouseToChessFace (event->x (), event->y ());
            emit		signal_mouseEvent_r \
                (releaseij.Chessi, releaseij.Chessj);
            //qDebug ()<<"release"<<releaseij.Chessi<<releaseij.Chessj<<"********************";
            //qDebug ()<<"side:"<<cface->side;

            this->ChessMoveCMan (pressij, releaseij);
        }
    if(SELECT_CONTROL_MODE == cface->controlMODE_flag)
    {
    }
    }
}

/*
 * 重定义的鼠标移动事件
 */
void		
Chess::mouseMoveEvent (QMouseEvent * event)
{
    if(DRAG_CONTROL_MODE == cface->controlMODE_flag)
    {
    //鼠标左键按下的情况移动 为拖动 即为走棋
    if(mousePress)
    {
        //移动中的信号转化成键值
        moveij= cface->mouseToChessFace (event->x (), event->y ());
        //发送移动的信号
	emit		signal_mouseEvent_m (moveij.Chessi, moveij.Chessj);
    }
    else // 否则为移动
    {
        //修改标志
        mouseRelease = false;
    }
    }

}

/*
 *  根据选择的棋子的原目标和位置目标 处理下棋流程控制的主函数
 */
void
Chess::ChessMoveCMan (ChessIJ	srcij, ChessIJ	destij)
{
    //qDebug ()<<"srcij"<<srcij.Chessi<<" "<<srcij.Chessj<<"id"<<cface->Chessface[srcij.Chessi][srcij.Chessj].Chessid;
    //qDebug ()<<"destij"<<destij.Chessi<<" "<<destij.Chessj<<"id"<<cface->Chessface[destij.Chessi][destij.Chessj].Chessid;;
    //调用棋局棋步  不满足棋步则将移动了的棋子归位
    if(cface->ChessProc (cface, srcij, destij))//不满足走棋过程的情况
    {
        //qDebug ()<<"Not Rule";
        //gui wei
        cface->Chessface[srcij.Chessi][srcij.Chessj].Chessij.Chessi = srcij.Chessi;
        cface->Chessface[srcij.Chessi][srcij.Chessj].Chessij.Chessj = srcij.Chessj;
        //发送当前走棋状态 选择的棋子 走棋的源位置 目标位置
        emit		signal_chessproc_status (cface->Chessface[srcij.Chessi][srcij.Chessj].Chessid, \
                    srcij,  destij, False);
    }
    else //满足走棋过程的  则走棋成功
    {
        //qDebug ()<<"Can Move";
        //选择了可悔棋  才把棋局保存
        if(cundo->UndoStep_set > 0)
        {
            cundo->ChessUndoPush (*uface);//把之前的棋局存入悔棋对象
        }
        //能悔棋则使悔棋键使能
        emit		signal_action_undo_enable(cundo->UndoStep);
        //发送当前走棋状态 选择的棋子 走棋的源位置 目标位置 走棋成功与否
        emit		signal_chessproc_status (cface->Chessface[destij.Chessi][destij.Chessj].Chessid, \
                    srcij,  destij, True);
        //走完一步棋后  进行是否将军的检查
        if(cface->ChessCheck (cface))
        {
            emit		signal_chesscheck ();
        }
    }
    //走棋完成后 判断双方的将是否存在 存在则继续走棋 否则 显示对方获胜
    if(R_K != cface->Chessface[cface->R_K_IJ.Chessi][cface->R_K_IJ.Chessj].Chessid)
    {
        qDebug ()<<"R_K id"<<cface->Chessface[cface->R_K_IJ.Chessi][cface->R_K_IJ.Chessj].Chessid;
        //红方将不存在了 发送黑方胜利的信号
        emit		signal_gameover (BLACK);
    }
    if(B_K != cface->Chessface[cface->B_K_IJ.Chessi][cface->B_K_IJ.Chessj].Chessid)
    {
        //黑方将不存在了 发送红方胜利的信号
        qDebug ()<<"B_K id"<<cface->Chessface[cface->B_K_IJ.Chessi][cface->B_K_IJ.Chessj].Chessid;
        emit		signal_gameover (RED);
    }

    //轮换玩家  发出此信号进行 头像切换 状态栏显示等处理
    emit		signal_turnSide (this->cface->side);
    this->update ();
}
/*
 * 槽函数 
 */
void		
Chess::slot_mouseEvent_p (int , int )
{
    //qDebug ()<<"clicks"<<clicks;
    //qDebug ()<<"counterR"<<cface->red_step_counter<<"contunterB"<<cface->black_step_counter;
    this->update ();
}

void		
Chess::slot_mouseEvent_r (int , int )
{
}
/*
 * 接收移动的信号 改变相对应的棋子键值 使棋子移动
 */
void		
Chess::slot_mouseEvent_m (int i, int j)
{
    int		chessman = cface->mouseToChessid (cface, pressij);
    if(cface->side == chessman)//只能拖动执子方的棋子
    {
        cface->Chessface[pressij.Chessi][pressij.Chessj].Chessij.Chessi = i;
        cface->Chessface[pressij.Chessi][pressij.Chessj].Chessij.Chessj = j;
    }
    this->update ();
}
