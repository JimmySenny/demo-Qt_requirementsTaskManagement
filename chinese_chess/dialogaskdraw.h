/***************************************************************************
  * Description:    实现求和认输确认的弹窗 此弹窗需和主窗体交互
  * Author  : As_ming
  * Language: c++/Qt
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef DIALOGASKDRAW_H
#define DIALOGASKDRAW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

/*
 * 此弹窗是一个确认的弹窗
 * 主要是和主窗体的信息交互
 */
class DialogAskDraw : public QDialog
{
    Q_OBJECT
public:
    explicit DialogAskDraw(int	side, QWidget *parent = 0);

	QLabel *      label_show;
	QPushButton * btn_agree;
	QPushButton * btn_refuse;
signals:
    //发送同意或拒绝的信号
	void		signal_draw_resp (int);//求和回复的信号
    
public slots:
    //当同意按钮按下的槽函数
	void		slot_btn_agree_clicked ();
    //当拒绝按钮按下的槽函数
	void		slot_btn_refuse_clicked ();
};

#endif // DIALOGASKDRAW_H
