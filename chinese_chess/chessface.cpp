/***************************************************************************
 * Description:    对棋局类声明的具体实现
 * Author  : As_ming
 * Language: c/c++/Qt
 * Features: 
 * Revision: 
 * Date    : 2012-05-04
 ***************************************************************************/

#include "chessface.h"
#include "basedefine.h"

//静态变量存控制走棋的模式  避免新游戏的开始使得模式改变
int	ChessFace::controlMODE_flag = DRAG_CONTROL_MODE;	//初始设置为拖动模式

ChessFace::ChessFace()
{
}
/*
 * 初始化棋盘信息 在新游戏时调用
 * Input    void
 * Output   void
 */
void		
ChessFace::initChessFace()
{
    //将资源文件中的棋子图片名称排列到数组中备用
    const char * chessimage[22] = { ":/B_J.png", ":/B_M.png", ":/B_X.png", ":/B_S.png",
        ":/B_K.png", ":/B_S.png", ":/B_X.png", ":/B_M.png",
        ":/B_J.png", ":/B_P.png", ":/B_Z.png",
        ":/R_J.png", ":/R_M.png", ":/R_X.png", ":/R_S.png",
        ":/R_K.png", ":/R_S.png", ":/R_X.png", ":/R_M.png",
        ":/R_J.png", ":/R_P.png", ":/R_B.png"};
    //将宏定义中的棋子id的名称排列备用
    const short	chessid[22] = { B_J, B_M, B_X, B_S, B_K, B_S, B_X, B_M, B_J, B_P, B_Z,
        R_J, R_M, R_X, R_S, R_K, R_S, R_X, R_M, R_J, R_P, R_B, };
    //i为行,j为列
    int j = 0;
    for(int i = 0; i < 10; i++)
    {
        //初始化时 以下行没有棋子 故给值 NO_CHESSMAN
        if(1 == i || 4 == i || 5 == i || 8 == i)
        {
            for(j = 0; j < 9; j++)
            {
                Chessface[i][j].Chessid = NO_CHESSMAN;
            }
        }
        //第0行黑方 车马相士将士相马车
        if(0 == i)//
        {
            for(j = 0; j < 9; j++)//棋盘的横方向
            {
                //载入上面排列好的图片名称即将图片载入相应位置的棋子
                Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[j]));
                //载入上面排列好的棋子名称即将棋子id赋值
                Chessface[i][j].Chessid = chessid[j];
                //相应的坐标赋值给相应的键值对
                Chessface[i][j].Chessij.Chessi = i;
                Chessface[i][j].Chessij.Chessj = j;
            }
        }
        //黑方  炮  炮
        if(2 == i)
        {
            for(j = 0; j < 9; j++)
            {
                //两个炮位
                if(1 == j || 7 == j)
                {
                    Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[9]));
                    Chessface[i][j].Chessid = chessid[9];
                    Chessface[i][j].Chessij.Chessi = i;
                    Chessface[i][j].Chessij.Chessj = j;
                }
                //其他位没棋子
                else
                {
                    Chessface[i][j].Chessid = NO_CHESSMAN;
                }//if
            }//for
        }//if
        //黑方 卒
        if(3 == i)
        {
            for(j = 0; j < 9; j++)
            {
                //有卒子的
                if((0 == j) || (2 == j) || (4 == j) || (6 == j) || (8 == j))
                {
                    Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[10]));
                    Chessface[i][j].Chessid = chessid[10];
                    Chessface[i][j].Chessij.Chessi = i;
                    Chessface[i][j].Chessij.Chessj = j;
                }
                //没卒的
                else
                {
                    Chessface[i][j].Chessid = NO_CHESSMAN;
                }
            }
        }
        //红方的兵
        if(6 == i)
        {
            for(j = 0; j < 9; j++)
            {
                if((0 == j) || (2 == j) || (4 == j) || (6 == j) || (8 == j))
                {
                    Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[21]));
                    Chessface[i][j].Chessid = chessid[21];
                    Chessface[i][j].Chessij.Chessi = i;
                    Chessface[i][j].Chessij.Chessj = j;
                }
                else
                  Chessface[i][j].Chessid = NO_CHESSMAN;
            }
        }
        //红方的炮
        if(7 == i)
        {
            for(j = 0; j < 9; j++)
            {
                if(1 == j || 7 == j)
                {
                    Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[20]));
                    Chessface[i][j].Chessid = chessid[20];
                    Chessface[i][j].Chessij.Chessi = i;
                    Chessface[i][j].Chessij.Chessj = j;
                }
                else
                {
                    Chessface[i][j].Chessid = NO_CHESSMAN;
                }//if
            }//for

        }
        //红方的    车马相士将士相马车
        if(9 == i)
        {
            for(j = 0; j < 9; j++)//棋盘的横方向
            {
                Chessface[i][j].Chessimage.load (QString("%1").arg (chessimage[j+11]));
                Chessface[i][j].Chessid = chessid[j+11];
                Chessface[i][j].Chessij.Chessi = i;
                Chessface[i][j].Chessij.Chessj = j;
            }
        }

    }//for i

    //初始时红方先走 故红方执棋
    side = RED;
    step_counter = 0;

    //将红黑方的将位置保存备用
    B_K_IJ = Chessface[0][4].Chessij;
    R_K_IJ = Chessface[9][4].Chessij;
}


/*
 * 位置转坐标 
 * 将鼠标在窗口中的位置position转换成棋盘矩阵上的行列坐标(键值对)
 * 棋盘位置              
 * o-------->x方向      
 * |
 * |
 * y方向
 * 键值对
 * <0, 0>----->j
 *   |
 *   |
 *   i
 * Input    窗口上棋盘的鼠标实际位置  
 * Output   棋盘矩阵坐标
 */
ChessIJ	
ChessFace::mouseToChessFace (int board_x, int board_y)	
{
    ChessIJ currentij;
    //y 坐标整除棋格宽度即为 i的键值
    //x 坐标整除棋格宽度即为 j的键值
    currentij.Chessi = board_y / BWA;
    currentij.Chessj = board_x / BWA;

    //对转换出来的键值对进行判断 若在棋盘外面则重新赋值为 <-1, -1>
    if(currentij.Chessi < 0 || currentij.Chessi > 9 || currentij.Chessi < 0 || currentij.Chessj > 8)
    {
        currentij.Chessi = -1;
        currentij.Chessj = -1;
    }
    //应为间隔的一半为2  远小于棋子宽度的一半25 故两棋子中间的间隔很小 不考虑点击在棋子之间的情况
    //合法则返回转换好的键值对
    return currentij;
}

/*
 * 判断当前鼠标点击的棋子是那一方的
 * Input    当前棋局的应用的指针    点击位置
 * Output   R_CHESSMAN  / B_CHESSMAN /  NONE
 */
int		
ChessFace::mouseToChessid(ChessFace  *& cface, ChessIJ & press)	//鼠标点击的是什么棋子
{
    //点击位置的棋子id
    int	chessid = cface->Chessface[press.Chessi][press.Chessj].Chessid;

    //判断
    if(R_CHESSMAN == IsRed (chessid))
      return R_CHESSMAN;
    if(B_CHESSMAN == IsBlack (chessid))
      return B_CHESSMAN;
    return NONE;
}

/***************************************************************************
 * Description:	rule of the chinese chess move
 * Author  : As_ming
 * Features:
 * Input:	当前棋局 和 包含棋子移动的信息(起始位置，目标位置) 
 * Output:	符合则返回true  否则返回False
 * Revision:
 * Date    : 2012-04-14
 **************************************************************************/
int		
ChessFace::ChessMoveRule (ChessFace  *& cface, ChessIJ & from, ChessIJ & to)
{
    int     count = 0;
    //存原位置的棋子id
    int	    prechessId = cface->Chessface[from.Chessi][from.Chessj].Chessid;	
    //存移到目标位置的棋子id
    int 	aftchessId = cface->Chessface[to.Chessi][to.Chessj].Chessid;	

    int i = from.Chessi; 	//原位置的键值 i的值
    int j = from.Chessj;	//原位值的键值 j的值

    //原位置没有棋子的情况
    if(NO_CHESSMAN == prechessId)
      return False;

    //棋子没有动的情况
    if((from.Chessi == to.Chessi) && 
                (from.Chessj == to.Chessj))
      return False;

    //棋子移动到棋盘外的情况
    if((to.Chessi > 9) || (to.Chessi < 0) || 
                (to.Chessj > 8) || (to.Chessj < 0))
      return False;

    //落点是己方棋子的情况
    if(!IsSameSide (prechessId, aftchessId))
      return False;

    /*
     * 每种棋子的移动规则
     */
    switch(prechessId)
    {
        // 将 帅 规则:在九宫内只走直线上一步
        case R_K:
            {
                //红方将不能出红方九宫
                if(to.Chessj < 3 || to.Chessj > 5 || to.Chessi < 7)
                  return False;
                //走了斜线或2步以上的情况
                if(abs(from.Chessi - to.Chessi) + abs(from.Chessj - to.Chessj) > 1)
                  return False;
                //照面的情况 在棋面规则中
                /* 
                   if((from.Chessi == to.Chessi) && (B_K_IJ.Chessj == to.Chessj)) //横走且目标位置与黑将一列
                   {
                //qDebug ()<<"照面";
                //qDebug ()<<"B_K"<<B_K_IJ.Chessj;
                int count = 0;
                for(int k = B_K_IJ.Chessi + 1;  k < to.Chessi; k++)
                {
                if(NO_CHESSMAN != cface->Chessface[k][to.Chessj].Chessid)	//存在棋子
                count++;
                }
                if(0 == count)
                return False;
                }
                */
                //更新将位信息
                cface->R_K_IJ = to;
                break;
            }
        case B_K:
            {
                //黑方帅不能出黑方九宫
                if(to.Chessj < 3 || to.Chessj > 5 || to.Chessi > 2)
                  return False;
                //走了斜线或2步以上的情况
                if(abs(from.Chessi - to.Chessi) + abs(from.Chessj - to.Chessj) > 1)
                  return False;
                //照面的情况
                /*
                   if((from.Chessi == to.Chessi) && (R_K_IJ.Chessj == to.Chessj)) //横走且目标位置与黑将一列
                   {
                   qDebug ()<<"照面";
                   int count = 0;
                   for(int k = R_K_IJ.Chessi - 1;  k > to.Chessi; k--)
                   {
                   if(NO_CHESSMAN != cface->Chessface[k][to.Chessj].Chessid)	//存在棋子
                   count++;
                   }
                   if(0 == count)
                   return False;
                   }
                   */
                cface->B_K_IJ = to;
                break;
            }
            // 士   规则:在九宫内走斜线一步
        case R_S:
            {
                //红士只能在红九宫的特定点
                if(!(((to.Chessi == 9) && (to.Chessj == 3)) ||
                                ((to.Chessi == 7) && (to.Chessj == 3)) ||
                                ((to.Chessi == 8) && (to.Chessj == 4)) ||
                                ((to.Chessi == 9) && (to.Chessj == 5)) ||
                                ((to.Chessi == 7) && (to.Chessj == 5))))
                  return False;
                //走的不是斜线一步
                if(abs(from.Chessj - to.Chessj) > 1 || abs(to.Chessi - from.Chessi) > 1)
                  return False;
                break;
            }
        case B_S:
            {
                //黑士只能在黑九宫的特定点
                if(!(((to.Chessi == 0) && (to.Chessj == 3)) ||
                                ((to.Chessi == 2) && (to.Chessj == 3)) ||
                                ((to.Chessi == 1) && (to.Chessj == 4)) ||
                                ((to.Chessi == 0) && (to.Chessj == 5)) ||
                                ((to.Chessi == 2) && (to.Chessj == 5))))
                  return False;
                if(abs(from.Chessj - to.Chessj) > 1 || abs(to.Chessi - from.Chessi) > 1)
                  return False;
                break;
            }
            // 相   规则：在己方棋盘里走田
        case R_X:
            {
                //红方的7个相位
                if(!(((to.Chessi == 7) && (to.Chessj == 0)) ||
                                ((to.Chessi == 9) && (to.Chessj == 2)) ||
                                ((to.Chessi == 5) && (to.Chessj == 2)) ||
                                ((to.Chessi == 7) && (to.Chessj == 4)) ||
                                ((to.Chessi == 9) && (to.Chessj == 6)) ||
                                ((to.Chessi == 5) && (to.Chessj == 6)) ||
                                ((to.Chessi == 7) && (to.Chessj == 8))))
                  return False;
                //走的不是田
                if(abs(from.Chessi - to.Chessi) != 2 || abs(from.Chessj - to.Chessj) != 2)
                  return False;
                //相心有棋子时不能走
                if(NO_CHESSMAN != cface->Chessface[(from.Chessi + to.Chessi)/2] \
                            [(from.Chessj + to.Chessj)/2].Chessid)
                  return False;
                break;
            }
        case B_X:
            {
                //黑相的7个相位
                if(!(((to.Chessi == 2) && (to.Chessj == 0)) ||
                                ((to.Chessi == 0) && (to.Chessj == 2)) ||
                                ((to.Chessi == 4) && (to.Chessj == 2)) ||
                                ((to.Chessi == 2) && (to.Chessj == 4)) ||
                                ((to.Chessi == 0) && (to.Chessj == 4)) ||
                                ((to.Chessi == 4) && (to.Chessj == 6)) ||
                                ((to.Chessi == 2) && (to.Chessj == 8))))
                  return False;
                //走的不是田
                if(abs(from.Chessi - to.Chessi) != 2 || abs(from.Chessj - to.Chessj) != 2)
                  return False;
                //相心有棋子时不能走
                if(NO_CHESSMAN != cface->Chessface[(from.Chessi + to.Chessi)/2] \
                            [(from.Chessj + to.Chessj)/2].Chessid)
                  return False;
                break;
            }
            //兵    规则：只能走一步 没过河不能横走 不得后退
        case R_B:
            {
                //红兵向上 不能退
                if(to.Chessi > from.Chessi)
                  return False;
                //红兵在红方的棋盘内不能横走
                if((from.Chessi >= 5) && (from.Chessj != to.Chessj))
                  return False;
                //红兵不能超过一步 不能斜走
                if(abs(from.Chessi - to.Chessi) + abs(from.Chessj - to.Chessj) > 1)
                  return False;
                break;
            }
        case B_Z:
            {
                //黑卒向下 不能退
                if(to.Chessi < from.Chessi)
                  return False;
                // 过河才能横走
                if((from.Chessi <= 4) && (from.Chessj != to.Chessj))
                  return False;
                //黑卒不能超过一步 不能斜走
                if(abs(from.Chessi - to.Chessi) + abs(from.Chessj - to.Chessj) > 1)
                  return False;
                break;
            }
            //车    规则: 只能直走 不能越过棋子
        case R_J:
        case B_J:
            // 炮   规则: 只能直走 不吃子时和车一样 吃子时只能越过一个棋子
        case R_P:
        case B_P:
            {
                //炮不吃子时 炮只能走直线 车也只能走直线
                if((from.Chessj != to.Chessj) && (from.Chessi != to.Chessi))
                  return False;
                //炮不吃子时 经过的路线中不能有棋子 车经过的路线中也不能有棋子
                if(((NO_CHESSMAN == cface->Chessface[to.Chessi][to.Chessj].Chessid) && //炮不吃子时的情况
                                ((R_P == prechessId) || (B_P == prechessId))) ||
                            ((R_J == prechessId) || (B_J == prechessId)))    //车的情况	
                {
                    if(from.Chessj == to.Chessj) //竖走
                    {
                        if(from.Chessi < to.Chessi) //向下走
                        {
                            for(i += 1; i < to.Chessi; i++)
                              if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//存在棋子
                                return False;
                        }
                        else//向上走
                        {
                            for(i -= 1; i > to.Chessi; i--)
                              if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//存在棋子
                                return False;
                        }

                    }
                    else	//横走
                    {
                        if(from.Chessj < to.Chessj)//向右走
                        {
                            for(j += 1; j < to.Chessj; j++)
                              if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//存在棋子
                                return False;
                        }
                        else// 向左走
                        {
                            for(j -= 1; j > to.Chessj; j--)
                              if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//存在棋子
                                return False;
                        }
                    }
                    break;
                }//炮不吃子的情况结束
                //炮吃子的情况
                if(from.Chessj == to.Chessj) //竖走
                {
                    if(from.Chessi < to.Chessi)	//向下走
                    {
                        for(i += 1; i < to.Chessi; i++)
                          if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//路线中存在棋子 计数器加1
                            count++;
                        if(1 != count)	//存在的子不等于1时
                          return False;
                    }
                    else //向上走
                    {
                        for(i -= 1; i > to.Chessi; i--)
                          if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//路线中存在棋子 计数器加1
                            count++;
                        if(1 != count)	//存在的子不等于1时
                          return False;
                    }

                }
                else	//横走的情况
                {
                    if(from.Chessj < to.Chessj)	//向右走
                    {
                        for(j += 1; j < to.Chessj; j++)
                          if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//路线中存在棋子 计数器加1
                            count++;
                        if(1 != count)	//存在的子不等于1时
                          return False;
                    }
                    else //向左走
                    {
                        for(j -= 1; j > to.Chessj; j--)
                          if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//路线中存在棋子 计数器加1
                            count++;
                        if(1 != count)	//存在的子不等于1时
                          return False;
                    }
                }
                break;
            }//炮 和 车 规则结束
            // 马   规则: 走日
        case R_M:
        case B_M:
            {
                if(!(((abs(to.Chessi - from.Chessi) == 1) && 	//上下走日
                      (abs(to.Chessj - from.Chessj) == 2)) ||
                     ((abs(to.Chessi - from.Chessi) == 2) &&	//左右走日
                      (abs(to.Chessj - from.Chessj) == 1))))
                  return False;
                //马脚的位置
                //向下走日  马脚在from.x + 1处
                if(2 == to.Chessi - from.Chessi) {
                    i++;//
                }
                //向上走日
                else if(2 == from.Chessi - to.Chessi) {
                    i--;
                }
                //向右走日 马脚在from.y + 1处
                else if(2 == to.Chessj - from.Chessj) {
                    j++;
                }
                //向左走日
                else if(2 == from.Chessj - to.Chessj) {
                    j--;
                }
                //看是否拌马脚
                if(NO_CHESSMAN != cface->Chessface[i][j].Chessid)	//马脚位置处有子
                  return False;
                break;
            }//马规则结束
        default:
            break;
    }//switch结束

    return True;	//移动规则通过  则返回True
}


/* 
 * 更新棋盘矩阵上的棋子信息 符合规则的被吃或移动后可被调用
 * Input    棋盘矩阵坐标  
 * Output   成功 返回True 否则返回 False
 */
void
ChessFace::updateChessFaceMan(ChessFace *& cface, \
            ChessIJ & srcij, ChessIJ & desij)
{
    //原位置的坐标棋子对象复制到目标位置的坐标的棋子对象
	if(DRAG_CONTROL_MODE == controlMODE_flag)
	{
		cface->Chessface[desij.Chessi][desij.Chessj] =
			cface->Chessface[srcij.Chessi][srcij.Chessj];
	}
	if(SELECT_CONTROL_MODE == controlMODE_flag)
	{
		cface->Chessface[srcij.Chessi][srcij.Chessj].Chessij=desij;
		cface->Chessface[desij.Chessi][desij.Chessj] =
			cface->Chessface[srcij.Chessi][srcij.Chessj];
	}

    //原位置的棋子信息清零
    cface->Chessface[srcij.Chessi][srcij.Chessj].Chessid = NO_CHESSMAN;
    cface->Chessface[srcij.Chessi][srcij.Chessj].Chessimage.load (":/no_chessman");
    cface->Chessface[srcij.Chessi][srcij.Chessj].Chessij.Chessi = srcij.Chessi;
    cface->Chessface[srcij.Chessi][srcij.Chessj].Chessij.Chessj = srcij.Chessj;

    //qDebug ()<<"updatesrc"<<cface->Chessface[srcij.Chessi][srcij.Chessj].Chessid;
    //qDebug ()<<"updatedes"<<cface->Chessface[desij.Chessi][desij.Chessj].Chessid;
}

/*
 *  判断棋面是否符合棋面规则
 */
int		
ChessFace::ChessNormal (ChessFace  cface)
{
    //qDebug ()<<B_K_IJ.Chessi<<"=============="<<B_K_IJ.Chessj<<"xx"<<R_K_IJ.Chessi<<"=============="<<R_K_IJ.Chessj;
    //判断有无将照面的情况
    if(cface.B_K_IJ.Chessj == cface.R_K_IJ.Chessj)
    {
        int count = 0;
        for(int k = B_K_IJ.Chessi + 1;  k < R_K_IJ.Chessi; k++)
        {
            if(NO_CHESSMAN != cface.Chessface[k][B_K_IJ.Chessj].Chessid)	//存在棋子
              count++;
        }
        //红将和黑帅之间若无棋子 则不合规则
        if(0 == count)
          return False;
    }
    return True;
}

/*
 * 判断当前棋局有无将军情况
 * Input    当前棋局的指针
 * Output   没有将军返回True 将军则返回False
 */
int		
ChessFace::ChessCheck (ChessFace *& cface)
{
    //红方被将军的情况
    if(RED == cface->side)
    {
        //被车或炮将
        for(int k = 0; k < 10; k++)
        {
            //竖方向被车将
            if(cface->Chessface[k][R_K_IJ.Chessj].Chessid == B_J)
            {
                if(k < R_K_IJ.Chessj)//车在红将的上面
                {
                    int count = 0;
                    for(int m = k + 1; m < R_K_IJ.Chessi; m++)
                      if(NO_CHESSMAN != cface->Chessface[m][R_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int m = k - 1; m > R_K_IJ.Chessi; m--)
                      if(NO_CHESSMAN != cface->Chessface[m][R_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
            }//竖方向车将结束
            //竖方向被炮将
            if(cface->Chessface[k][R_K_IJ.Chessj].Chessid == B_P)
            {
                if(k < R_K_IJ.Chessi)//炮在红将的左边
                {
                    int count = 0;
                    for(int m = k + 1; m < R_K_IJ.Chessi; m++)
                      if(NO_CHESSMAN != cface->Chessface[m][R_K_IJ.Chessi].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int m = k - 1; m > R_K_IJ.Chessi; m--)
                      if(NO_CHESSMAN != cface->Chessface[m][R_K_IJ.Chessi].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }//if-else
            }// 竖方向被炮将结束
            //横方向 少一列
            if(10 == k)
              continue;
            //横方向有车时
            if(cface->Chessface[R_K_IJ.Chessi][k].Chessid == B_J)
            {
                if(k < R_K_IJ.Chessj)//车在红将的左边
                {
                    int count = 0;
                    for(int n = k + 1; n < R_K_IJ.Chessj; n++)
                      if(NO_CHESSMAN != cface->Chessface[R_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int n = k - 1; n > R_K_IJ.Chessj; n--)
                      if(NO_CHESSMAN != cface->Chessface[R_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
            }//横方向 车
            //横方向有炮时
            if(cface->Chessface[R_K_IJ.Chessi][k].Chessid == B_P)
            {
                if(k < R_K_IJ.Chessj)//炮在红将的左边
                {
                    int count = 0;
                    for(int n = k + 1; n < R_K_IJ.Chessj; n++)
                      if(NO_CHESSMAN != cface->Chessface[R_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int n = k - 1; n > R_K_IJ.Chessj; n--)
                      if(NO_CHESSMAN != cface->Chessface[R_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }//if-else
            }//横方向 炮结束
        }//炮和车将结束
        //被卒将    红将上 左 右 就有黑方的卒
        if((B_Z == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj].Chessid)	||//上
           (B_Z == cface->Chessface[R_K_IJ.Chessi][R_K_IJ.Chessj - 1].Chessid)	||//左
           (B_Z == cface->Chessface[R_K_IJ.Chessi][R_K_IJ.Chessj + 1].Chessid))//右
          return		False;
        //被马将    距将一个日的点位 
        switch(R_K_IJ.Chessi)
        {
            case    7://若将在第七行  则有8个点位可被马将
                //这是被底线的马竖方向日将的情况
                if(((B_M == cface->Chessface[R_K_IJ.Chessi + 2][R_K_IJ.Chessj + 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj + 1].Chessid))	||
                   ((B_M == cface->Chessface[R_K_IJ.Chessi + 2][R_K_IJ.Chessj - 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj - 1].Chessid)))
                  return		False;
                //无break
            case    8://若将在第八行 则有6个点位可被马将
                //这是被底线的马横方向日将的情况
                if(((B_M == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj + 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj + 1].Chessid))	||
                   ((B_M == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj - 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi + 1][R_K_IJ.Chessj - 1].Chessid)))
                  return		False;
                //无break
            case	9://若将在底线  则只有4个点可被马将
                //这是被红将 上方的马踩的情况
                if(((B_M == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj + 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj + 1].Chessid))	||
                   ((B_M == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj - 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj - 1].Chessid))		||
                   ((B_M == cface->Chessface[R_K_IJ.Chessi - 2][R_K_IJ.Chessj + 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj + 1].Chessid))	||
                   ((B_M == cface->Chessface[R_K_IJ.Chessi - 2][R_K_IJ.Chessj - 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj - 1].Chessid)))
                  return		False;
                //有break
                break;
            default:
                break;
        }

    }// RED方结束
    else//黑方被将军
    {
        //黑将和被车或炮将军时
        for(int k = 0; k < 10; k++)
        {
            //竖方向
            if(cface->Chessface[k][B_K_IJ.Chessj].Chessid == R_J)
            {
                if(k < B_K_IJ.Chessi)//车在红将的上面
                {
                    int count = 0;
                    for(int m = k + 1; m < B_K_IJ.Chessi; m++)
                      if(NO_CHESSMAN != cface->Chessface[m][B_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int m = k - 1; m > B_K_IJ.Chessi; m--)
                      if(NO_CHESSMAN != cface->Chessface[m][B_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
            }//竖方向车结束
            //竖方向炮
            if(cface->Chessface[k][B_K_IJ.Chessj].Chessid == R_P)
            {
                if(k < B_K_IJ.Chessi)//炮在黑将的上边
                {
                    int count = 0;
                    for(int m = k + 1; m < B_K_IJ.Chessi; m++)
                      if(NO_CHESSMAN != cface->Chessface[m][B_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }
                else//炮在黑将下边
                {
                    //qDebug ()<<"test---------------";
                    int count = 0;
                    for(int m = k - 1; m > B_K_IJ.Chessi; m--)
                      if(NO_CHESSMAN != cface->Chessface[m][B_K_IJ.Chessj].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }//if-else
            }// 竖方向炮
            //横方向
            if(10 == k)
              continue;
            //横方向有车时
            if(cface->Chessface[B_K_IJ.Chessi][k].Chessid == R_J)
            {
                if(k < B_K_IJ.Chessj)//车在红将的左边
                {
                    int count = 0;
                    for(int n = k + 1; n < B_K_IJ.Chessj; n++)
                      if(NO_CHESSMAN != cface->Chessface[B_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int n = k - 1; n > B_K_IJ.Chessj; n--)
                      if(NO_CHESSMAN != cface->Chessface[B_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(0 == count)
                      return False;
                }
            }//横方向 车
            //有炮时
            if(cface->Chessface[B_K_IJ.Chessi][k].Chessid == R_P)
            {
                if(k < B_K_IJ.Chessj)//炮在红将的左边
                {
                    int count = 0;
                    for(int n = k + 1; n < B_K_IJ.Chessj; n++)
                      if(NO_CHESSMAN != cface->Chessface[B_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }
                else
                {
                    int count = 0;
                    for(int n = k - 1; n > B_K_IJ.Chessj; n--)
                      if(NO_CHESSMAN != cface->Chessface[B_K_IJ.Chessi][n].Chessid)	//存在棋子
                        count++;
                    if(1 == count)
                      return False;
                }//if-else
            }//横方向 炮
        }//炮和车将结束
        //被卒将
        if((B_Z == cface->Chessface[R_K_IJ.Chessi - 1][R_K_IJ.Chessj].Chessid)	||
           (B_Z == cface->Chessface[R_K_IJ.Chessi][R_K_IJ.Chessj - 1].Chessid)	||
           (B_Z == cface->Chessface[R_K_IJ.Chessi][R_K_IJ.Chessj + 1].Chessid))
          return		False;
        //被马将
        switch(B_K_IJ.Chessi)
        {
            case	2:
                //被底线的马竖着日将
                if(((R_M == cface->Chessface[B_K_IJ.Chessi - 2][B_K_IJ.Chessj - 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj - 1].Chessid))	||
                   ((R_M == cface->Chessface[B_K_IJ.Chessi - 2][B_K_IJ.Chessj + 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj + 1].Chessid)))
                  return		False;
                //无break
            case 1:
                //被底线的马横着日将
                if(((R_M == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj + 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj + 1].Chessid))	||
                   ((R_M == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj - 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi - 1][B_K_IJ.Chessj - 1].Chessid)))
                  return		False;
                //无break
            case	0:
                //被黑将下方4个点将
                if(((R_M == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj + 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj + 1].Chessid))	||
                   ((R_M == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj - 2].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj - 1].Chessid))	||
                   ((R_M == cface->Chessface[B_K_IJ.Chessi + 2][B_K_IJ.Chessj + 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj + 1].Chessid))	||
                   ((R_M == cface->Chessface[B_K_IJ.Chessi + 2][B_K_IJ.Chessj - 1].Chessid)	&&
                    (NO_CHESSMAN == cface->Chessface[B_K_IJ.Chessi + 1][B_K_IJ.Chessj - 1].Chessid)))
                  return		False;
                //有break
                break;
            default:
                break;
        }
    }//BLACK方被将结束
    return True;
}

/* 
 * 走棋的过程   完成一步走棋和交换棋手的功能
 * Input    当前棋局指针  原位置 目标位置
 * Output   能够完成棋步 则返回True  否则返回False
 */
int		
ChessFace::ChessProc (ChessFace *& cface, ChessIJ & from, ChessIJ & to)
{
    //qDebug ()<<"from"<<from.Chessi<<","<<from.Chessj;
    //qDebug ()<<"to"<<to.Chessi<<","<<to.Chessj;
    //存原位置的棋子id
    int	chessId = cface->Chessface[from.Chessi][from.Chessj].Chessid;	

    //判断棋手和当前要走的棋子是否配对 不配对则返回False
    if(IsRightPlayer (cface->side, chessId))
      return	False;

    //走棋是否符合规则  不符和则返回False
    if(cface->ChessMoveRule (cface, from, to))
      return  False;

    //棋子移动符合规则的话 将棋局更新到临时棋局 然后再进行棋面规则判断
    ChessFace tempcface = *cface;
    tempcface.Chessface[from.Chessi][from.Chessj].Chessid = NO_CHESSMAN;
    tempcface.Chessface[to.Chessi][to.Chessj].Chessid = cface->Chessface[to.Chessi][to.Chessj].Chessid;

    //棋局是否符合规则 不符和则返回False
    if(cface->ChessNormal (tempcface))
      return	False;

    //规则都通过 则更新棋局信息
    updateChessFaceMan (cface, from, to);
	step_counter++;

    switch(cface->side)
    {
        //如果是红方执棋
        case RED:
            {
                //之后交换为黑方执棋
                cface->side = BLACK;
                break;
            }//RED
        //如果是黑方执棋
        case BLACK:
            {
                //之后交换为黑方执棋
                cface->side = RED;
                break;
            }//BLACK
        default:
            return False;
    }
    //棋步结束 返回True
    return True;
}
