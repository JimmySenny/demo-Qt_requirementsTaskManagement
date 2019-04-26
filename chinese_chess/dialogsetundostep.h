/***************************************************************************
  * Description:    可悔棋的步数可调  在这个弹窗中实现
  * Author  : As_ming
  * Language: c++/Qt
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef DIALOGSETUNDOSTEP_H
#define DIALOGSETUNDOSTEP_H

#include <QDialog>
#include <QSlider>
#include	 <QSpinBox>
#include <QLabel>
#include <QPushButton>

/*
 * 滑条和选择框用来选择 label用来显示  
 * 他们之间数值是关联的  
 * 确定按钮的按钮按下 则将选择的数值发送到主窗体  修改一系列的变量值
 */
class DialogSetUndostep : public QDialog
{
    Q_OBJECT
public:
    explicit DialogSetUndostep(QWidget *parent = 0);

    QSlider	*   slider;
    QSpinBox *  spinbox;
    QLabel	*   label;
    QPushButton * btn_ok;

signals:
    //将选择的数值发送到主窗体
    void		signal_undostep (int);
    
public slots:
    //确认按钮按下的槽函数 
    void		slot_btnok_clicked ();
};

#endif // DIALOGSETUNDOSTEP_H
