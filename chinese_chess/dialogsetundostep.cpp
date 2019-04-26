/***************************************************************************
  * Description:    选择悔棋步数弹窗的实现 
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#include "dialogsetundostep.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "basedefine.h"

DialogSetUndostep::DialogSetUndostep(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel("3", this);
	label->setFont (QFont("微软雅黑", 15, QFont::Bold));

    slider = new QSlider(this);
    //设置滑条横方向
    slider->setOrientation (Qt::Horizontal);
    //设置滑条范围 从0 到悔棋数组的最大值
    slider->setRange (0, MAX_UNDOSTEP);
    //设置初始值为3 
    slider->setValue (3);

    spinbox = new QSpinBox(this);
    spinbox->setRange (0, MAX_UNDOSTEP);
    spinbox->setValue (3);

    btn_ok = new QPushButton("确定", this);

    QHBoxLayout * horlayout = new QHBoxLayout;
    horlayout->addWidget (slider);
    horlayout->addWidget (spinbox);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget (label, 0, Qt::AlignCenter);
    layout->addLayout (horlayout);
    layout->addWidget (btn_ok, 0, Qt::AlignCenter);

    this->setLayout (layout);
    this->setWindowTitle ("设置悔棋步数");
    this->resize (320, 160);

    //滑条和选择框同步
    connect (slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    connect (spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    //数值显示到label上
    connect (slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
    //点击button要做的事情
    connect (btn_ok, SIGNAL(clicked()),this, SLOT(slot_btnok_clicked()));
}

/*
 * 设置好悔棋步数后  若确认 则将新值发送到主窗体 
 */
void		
DialogSetUndostep::slot_btnok_clicked ()
{
    int step;
    //获得所设置的值
    step = label->text ().toInt ();
    qDebug ()<<"setUndostep"<<step;
    //发送信号
    emit		signal_undostep (step);
    //usleep(1000);
    this->close ();
}
