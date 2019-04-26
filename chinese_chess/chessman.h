/***************************************************************************
  * Description:    对棋子类的声明
  * Author  : As_ming
  * Language: c++
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/

#ifndef CHESSMAN_H
#define CHESSMAN_H

#include "chessij.h"
#include <QImage>

/*
 * 将所有的棋子抽象为一个类 
 * 通过对这个类的实例化 将每个棋子具体实现
 * 棋子类具体包括:
 * 1.棋子的图片 每种棋子都有一种图像与之对应 QImage 是Qt的一种图像类
 * 2.棋子的id   每种棋子都有一个id号 
 *              象棋共有7种棋子 分为红黑两方 则共有14个id号
 * 3.棋子的键值对   棋子实例化时 要在棋盘上显示 
 *                  则必有键值对
 */
class	ChessMan
{
public:
    ChessMan();
    ~ChessMan(){}

    void		zeroChessMan();
	ChessMan & operator=(ChessMan & cman);

    QImage	Chessimage;
    int 	Chessid;
    ChessIJ	Chessij;
};

#endif // CHESSMAN_H
