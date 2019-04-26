/***************************************************************************
  * Description:    定义棋盘上键值对的类
  * Author  : As_ming
  * Language:   c++
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/
#ifndef CHESSIJ_H
#define CHESSIJ_H

#include "basedefine.h"

/*  
 *  棋盘上的键值对 <i, j>
 *  如下图所示棋盘键值对    i 为行坐标 j为列坐标
 *  --> j
 *  | <0, 0>  ...     <0, 8>
 *  i .
 *    .
 *    .
 *    <9, 0>  ...     <9, 8>
 */
class ChessIJ
{
public:
    ChessIJ();
	void		ReSetChessIJ ();
    bool		operator==(ChessIJ & ij)const;
    bool		operator!=(ChessIJ & ij)const;
    //ChessIJ  & operator=(ChessIJ & ij1);

    int 	Chessi;	
    int 	Chessj;
};

#endif // CHESSIJ_H
