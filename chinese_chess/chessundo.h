/***************************************************************************
 * Description:    悔棋类的抽象  完成象棋的悔棋功能
 * Author  : As_ming
 * Language: c/c++
 * Features: 
 * Revision: 
 * Date    : 2012-05-06
 ***************************************************************************/

#ifndef CHESSUNDO_H
#define CHESSUNDO_H

#include "chessface.h"

/*
 * 悔棋类主要就是对走过的棋局的保存 
 * 并将保存的棋局数组每走一步更新一次   
 */
class ChessUndo
{
    public:
        ChessUndo();
        ~ChessUndo(){}

        //初始化悔棋类的相应值
        void		initChessUndo();
        //重载 = 
        ChessUndo & operator=(ChessUndo & cundo);
        //将走棋之前的棋局入栈(数组) 每次走棋前都更新栈
        int		    ChessUndoPush (ChessFace cface);
        //将保存的棋局弹出 悔棋
        void		ChessUndoPop (ChessFace & uface);

        //棋局对象的数组用于存储悔棋的棋局
        ChessFace   Chessundo[MAX_UNDOSTEP];//最大可悔的棋步
        //自定义的悔棋步数 可调的
        int		    UndoStep_set;		//设置的悔棋步数
        //当前悔棋数组中已保存的可悔棋局
        int		    UndoStep;	//当前可悔棋的棋步数
};
#endif // CHESSUNDO_H
