#include "center.h"
#include "basedefine.h"
#include <QHBoxLayout>
#include <QDebug>
#include <stdio.h>

Center::Center(QWidget *parent)
    : QWidget(parent)
{

	chess = new Chess(this);
	sidebar = new SideBar(this);

	QHBoxLayout * mainlayout = new QHBoxLayout;
	mainlayout->addWidget (chess);
	mainlayout->addWidget (sidebar);

	this->setLayout (mainlayout);

	connect (sidebar, SIGNAL(signal_sidebar_start()), this, SLOT(slot_sidebar_btn_timerstart()));

	connect (chess, SIGNAL(signal_turnSide(int)), this, SLOT(slot_turnSide(int)));
}

void		Center::slot_sidebar_btn_timerstart ()
{
	chess->setEnabled (true);
}

void		Center::slot_turnSide (int side)
{
		if(RED == side)
			this->sidebar->turn2redpix ();

		if(BLACK == side)
			this->sidebar->turn2blackpix ();
	/*
	int	size_center 	= sizeof(*this);
	int	size_chess 	= sizeof(*this->chess);
	int	size_sidebar	= sizeof(*this->sidebar);
	int	size_cface		= sizeof(*this->chess->cface);
	int	size_cundo	= sizeof(*this->chess->cundo);

	qDebug ()<<"size_center"<<size_center;//28
	qDebug ()<<"size_chess"<<size_chess;//68
	qDebug ()<<"size_sidebar"<<size_sidebar;//80
	qDebug ()<<"size_cface"<<size_cface;//2180
	qDebug ()<<"size_cundo"<<size_cundo;//19628
	*/
}

