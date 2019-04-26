/***************************************************************************
  * Description:    关于象棋的基本宏定义
  * Author  : As_ming
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/

#ifndef BASEDEFINE_H
#define BASEDEFINE_H

#include <QDebug>

#define True		0
#define False		1

#define SUCCESS	    0
#define	 FAILURE	1

//车_J 马_M 相_X 士_S 将_K 炮_P 兵_B 卒_Z
#define NONE		0	//没有
#define RED			1	//红方
#define	BLACK		2	//黑方

#define BASIC_MODE	0   //基本模式
#define TIMER_MODE	1   //计时模式
#define MAX_TIME	30 * 60	//计时模式时的最大秒数   规则规定时30分钟

#define DRAG_CONTROL_MODE		0	//拖动控制走棋的模式
#define SELECT_CONTROL_MODE		1	//选择控制走棋的模式

#define MAX_UNDOSTEP 	9   //可以悔棋的最大步数
/* 棋子 棋盘------------------------------------ */
#define NO_CHESSMAN		0   //没有棋子
#define R_CHESSMAN		1   //红棋
#define B_CHESSMAN		2   //黑棋

#define R_K			1 //红	将
#define R_S			2 //	士
#define R_X			3 //	相
#define R_M			4 //	马
#define R_J			5 //	车
#define R_P			6 //	炮
#define R_B			7 //	兵
#define R_BEGIN		R_K
#define R_END		R_B

#define B_K			11 //黑	将
#define B_S			12 //	士
#define B_X			13 //	相
#define B_M			14 //	马
#define B_J			15 //	车
#define B_P			16 //	炮
#define B_Z			17 //	卒
#define B_BEGIN		B_K
#define B_END		B_Z

#define MW	    ManWidth		//棋子的半径
#define SW	    SpacingWidth	//棋子间隔的一半
#define BWA	    BoardWidthApiece//每个棋格的宽度
#define XBW	    XBoardWidth		//x方向的棋盘宽度
#define YBW	    YBoardWidth		//y方向的棋盘宽度

const	int		MW = 25;		//棋子的宽度
const	int		SW = 2;			//棋子间隔的一半
const	int		BWA = (MW + SW) * 2;	//棋格宽度
const	int 	XBW = BWA * 9;	//棋盘宽 = 棋格 * 9
const	int		YBW = BWA * 10;	//棋盘高 = 棋格 * 10
/*------------------------------------ 棋子 棋盘*/


/*接口------------------------------------ */
//判断某个棋子是不是红色
int		IsRed(int chessid);

//判断某个棋子是不是黑色(
int		IsBlack(int	chessid);

//判断两个棋子是否同色
int		IsSameSide(int chessid1, int chessid2);

//判断棋手是不是和棋子配对
int		IsRightPlayer(int player, int chessman);

/*----------------------------------- 接口*/


#endif // BASEDEFINE_H
