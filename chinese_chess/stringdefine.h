/***************************************************************************
  * Description:    常用的字符串的声明定义 可在其实现中快速全面的更改常用的字符串
  * Author  : As_ming
  * Language: 
  * Features: 
  * Revision: 
  * Date    : 2012-05-07
  ***************************************************************************/

#ifndef STRINGDEFINE_H
#define STRINGDEFINE_H

#include <QString>

class StringDefine
{
public:
    StringDefine();


	QString		str_tile_name;
	QString		str_waitstart;
	QString		str_start;
	QString		str_red_go;
	QString		str_black_go;
    QString		str_red_win;
    QString		str_black_win;
    QString		str_draw;
    QString		str_red_draw;
    QString		str_black_draw;
    QString		str_check;
    QString		str_no_cman;
    QString		str_no_rule;
    QString 	str_about;
};

#endif // STRINGDEFINE_H
