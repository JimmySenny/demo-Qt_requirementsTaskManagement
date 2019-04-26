/***************************************************************************
  * Description:    基本接口的实现
  * Author  : As_ming
  * Language: c
  * Features: 
  * Revision: 
  * Date    : 2012-05-01
  ***************************************************************************/

#include "basedefine.h"

/*
 * 判断某个棋子是不是红色
 * Input    棋子的id号
 * Output   R_CHESSMAN  / NONE
 */
int	IsRed(int chessid)
{
	if((chessid >= R_BEGIN) && (chessid <= R_END))
		return R_CHESSMAN;
	else
		return NONE;
}

/*
 * 判断某个棋子是不是黑色
 * Input    棋子的id号
 * Output   B_CHESSMAN  / NONE
 */
int	IsBlack(int	chessid)
{
	if((chessid >= B_BEGIN) && (chessid <= B_END))
		return B_CHESSMAN;
	else
		return NONE;
}

/*
 * 判断两个棋子是否同色
 * Input    2个棋子的id号
 * Output   True    /   False
 */
int	IsSameSide(int chessid1, int chessid2)
{
	if((IsRed(chessid1) == IsRed (chessid2)) && (IsRed (chessid1) != NONE))
		return True;
	if((IsBlack(chessid1) == IsBlack (chessid2)) && (IsBlack (chessid1) != NONE))
		return True;
	return False;
}

/*
 * 判断棋手是不是和棋子相应 
 * 红方执红棋  黑方执黑棋时 是为True 否则是为False
 * Input    当前执子方, 棋子id 
 * Output   True    /   False
 */
int		IsRightPlayer(int player, int chessid)
{
	if(RED == player)//红方棋手时
	{
		if(R_CHESSMAN == IsRed (chessid))//走的是红棋
			return True;
		else
			return False;
	}
	if(BLACK == player)//黑方棋手时
	{
		if(B_CHESSMAN == IsBlack (chessid))//走的是黑棋
			return True;
		else
			return False;
	}
	return False;
}
