#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>
#include "chess.h"
#include "sidebar.h"

class Center: public QWidget
{
    Q_OBJECT

protected:
public:
    explicit Center(QWidget *parent = 0);
    
signals:
    
public slots:
	void		slot_sidebar_btn_timerstart ();
	void		slot_turnSide (int);

public:
    Chess * chess;
    SideBar * sidebar;
};

#endif // CENTERWINDOW_H
