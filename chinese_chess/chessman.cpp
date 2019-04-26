/***************************************************************************
  * Description:    对棋子类的实现
  * Author  : As_ming
  * Language: c++
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/

#include "chessman.h"

/*
 * 构造函数
 */
ChessMan::ChessMan()
{
}

/*
 * 对一个棋子实例信息清零
 */
void		
ChessMan::zeroChessMan()
{
    Chessimage.load (":/no_chessman.png");
    Chessid = NO_CHESSMAN;
    Chessij.Chessi = -1;
    Chessij.Chessj = -1;
}

/*
  * 重载运算符 =
  */
ChessMan &
ChessMan::operator=(ChessMan & cman)
{
	this->Chessimage=cman.Chessimage;
	this->Chessid = cman.Chessid;
	this->Chessij.Chessi = cman.Chessij.Chessi;
	this->Chessij.Chessj = cman.Chessij.Chessj;

	return	*this;
}
