/***************************************************************************
  * Description:    弹出关于中国象棋游戏介绍的窗口  内容是从文件中读取  在窗口中显示
  * Author  : As_ming
  * Language: c++/Qt
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef DIALOGABOUTCCHESS_H
#define DIALOGABOUTCCHESS_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>

/*
 * 这个谈窗比较简单 只是弹出一个窗口  
 * 窗口中有文本框显示内容 有一个按钮用于关闭本弹窗
 */

class DialogAboutCChess : public QDialog
{
    Q_OBJECT
    public:
        explicit DialogAboutCChess(QWidget *parent = 0);

signals:

public slots:

private:
        QTextEdit * textedit; //文本框 显示关于中国象棋的内容
        QPushButton * btn_know; //上一页
};

#endif // DIALOGABOUTCCHESS_H
