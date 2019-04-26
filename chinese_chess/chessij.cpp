/***************************************************************************
  * Description:    对棋盘键值对的具体实现
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/

#include "chessij.h"

/*
 * 构造时赋初值 <-1, -1> 
 */
ChessIJ::ChessIJ()
{
	Chessi = -1;
	Chessj = -1;
}

void		ChessIJ::ReSetChessIJ ()
{
	Chessi = -1;
	Chessj = -1;
}

/*
 * 重载 == 运算符   以便对两个键值对相等进行判断
 */
bool		ChessIJ::operator==(ChessIJ & ij)const
{
	if((this->Chessi == ij.Chessi) && (this->Chessj == ij.Chessj))
		return true;
	return false;
}

/*
 * 重载 != 运算符   以便对两个键值对不相等进行判断
 */
bool		ChessIJ::operator!=(ChessIJ & ij)const
{
	if((this->Chessi == ij.Chessi) && (this->Chessj == ij.Chessj))
		return false;
	return true;
}

/*
ChessIJ	ChessIJ::operator = (ChessIJ & ij)
{
	this->Chessi = ij.Chessi;
	this->Chessj = ij.Chessj;
	return *this;
}
*/
