/***************************************************************************
  * Description:    棋局类的抽象声明
  * Author  : As_ming
  * Language: c/c++/Qt
  * Features: 
  * Revision: 
  * Date    : 2012-05-04
  ***************************************************************************/

#ifndef CHESSFACE_H
#define CHESSFACE_H

#include "chessman.h"

/*
 * 棋局就是整个棋盘的抽象  
 * 成员变量包括:
 * 1.棋盘矩阵   是一个二维数组 根据棋盘键值对 很容易将 <i, j>转换成棋盘矩阵上的 行，列坐标
 *              棋盘矩阵的类型是棋子类 即每个键值对上的棋子情况 
 *              有棋子则是具体的棋子对象 没棋子棋子对象的信息为零
 *              转换
 *              棋盘矩阵               <=>  棋盘键值对 <i, j>
 *              0行0列  ...     0行8列  |   <0, 0>      <0, 8>
 *              1行0列                  |
 *                .                     |
 *                .                     |
 *                .                     |
 *              9行0列  ...     9行9列  |   <9, 0>      <9, 8>
 * 2.全部在棋盘上的棋子
 * 3.执子方
 * 4.红黑方将的位置 将军和胜负情况的判断全部依赖与将的位置
 * 成员函数包括:
 * <1>鼠标事件   在棋盘上 棋子的走棋依赖于鼠标(在pc机上), 
 *              故还需要对鼠标事件进行重定义 以满足需求
 * <2>初始化棋盘
 * <3>位置转坐标 鼠标在窗口中的位置position转换成棋盘矩阵上的行列坐标(键值对)
 * <4>走棋的规则 象棋中每种棋子都有其相应的移动规则 
 *               根据选择的棋子、起始位置、到达位置 判断是否符合移动规则 此为象棋游戏算法的难点和关键 
 * <5>棋面的规则 象棋中一些移动符合规则但移动后不合规则的棋面 比如将照面等 在这里实现  是游戏算法的补充
 * <6>更新棋局   更新棋盘矩阵上的棋子信息  功能是清零一个键值对上的棋子 在有棋子移动后或被吃后调用
 * <7>将军提示   棋类游戏都有将军提示 对是否有将军的判断时对游戏的完善
 * <8>棋步过程   以上规则是单方面的  棋步过程将算法进行整合 完成一步走棋和交换棋手的功能
 */
class	ChessFace
{
public:
    ChessFace();
    ~ChessFace(){}

    //初始化棋盘
    void	initChessFace ();
    //将鼠标在棋盘上的实际点坐标转换成10*9矩阵的坐标
    ChessIJ	mouseToChessFace (int, int);
    //鼠标点击的是什么棋子
    int		mouseToChessid(ChessFace  *& cface, ChessIJ & press);
    //走棋是否符合基本规则
    int		ChessMoveRule (ChessFace *& cface, ChessIJ & from, ChessIJ & to);
    //棋面是否符合基本规则
    int		ChessNormal (ChessFace  cface);
    //判断是否被将军
    int		ChessCheck (ChessFace *& cface);
    //更新棋局
    void	updateChessFaceMan(ChessFace *&, ChessIJ &, ChessIJ &);
    //棋步的过程
    int		ChessProc(ChessFace *& cface, ChessIJ & from, ChessIJ & to);

    ChessMan    Chessface[10][9];	//棋盘矩阵
    ChessIJ 	R_K_IJ;
    ChessIJ	    B_K_IJ;
    int 		side;	//那方执子的标志
    int			step_counter;	//total step;
	static	int	controlMODE_flag;//走棋模式的标志

protected:
    void		slot_mouseEvent_press (int, int);
};

#endif // CHESSFACE_H
