/***************************************************************************
 * Description:    悔棋类的实现
 * Author  : As_ming
 * Language: 
 * Features: 
 * Revision: 
 * Date    : 2012-05-06
 ***************************************************************************/

#include "chessundo.h"

//构造
ChessUndo::ChessUndo()
{
    this->UndoStep_set = 3;
    this->UndoStep = 0;
}

/*
 *  初始化悔棋的对象
 */
void		
ChessUndo::initChessUndo()
{
    this->UndoStep_set = 3;
    this->UndoStep = 0;
}

/*
 *  重载的 = 
 */
ChessUndo & 
ChessUndo::operator=(ChessUndo & cundo)
{
    for(int k = 0; k < MAX_UNDOSTEP; k++)
    {
        Chessundo[k]=cundo.Chessundo[k];
    }

    UndoStep =cundo.UndoStep;
    return *this;
}

/*
 * 实现入栈的功能
 */
int		
ChessUndo::ChessUndoPush (ChessFace cface)
{
    //先依次后移  
    if(UndoStep < UndoStep_set)
      UndoStep++;
    int	i = UndoStep - 1;
    while(i)
    {
        Chessundo[i] = Chessundo[i-1];
        //qDebug ()<<"Chessundo:chessundo"<<&Chessundo[i];
        i--;
    }
    //再将第一个中放入最新的棋局 
    Chessundo[0] = cface;

    return UndoStep;
}

/*
 * 实现出栈的功能
 */
void		
ChessUndo::ChessUndoPop (ChessFace & uface)
{
    int i = 0;
    //出第一个 
    uface = Chessundo[0];
    //qDebug ()<<"Chessundo:uface"<<&uface;
    //将第一个以后的一次前移  
    for(; i < UndoStep - 1; i++)
    {
        Chessundo[i] = Chessundo[i + 1];
    }
    UndoStep--;
}
