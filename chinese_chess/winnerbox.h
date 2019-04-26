/***************************************************************************
  * Description:    自定义的弹窗  用于显示当前获胜方
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef WINNERBOX_H
#define WINNERBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

/*
 * 弹出当前棋局的获胜方
 * 然后对下一步处理的选择
 */
class WinnerBox : public QDialog
{
    Q_OBJECT
public:
    explicit WinnerBox(QString str, QWidget *parent = 0);
    QLabel	*     label;
    QPushButton * btn_restart;
    QPushButton * btn_quit;

signals:
    //发送退出游戏的信号
    void		signal_winnerbox_quit ();
    //发送重玩的信号
    void		signal_winnerbox_restart ();
    
public slots:
    //若选择不玩 则退出游戏
    void		slot_winnerbox_quit ();
    //若选择重新开始 则重玩一局
    void		slot_winnerbox_restart ();
};

#endif // WINNERBOX_H
