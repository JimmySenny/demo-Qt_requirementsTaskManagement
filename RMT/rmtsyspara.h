#ifndef RMTSYSPARA_H
#define RMTSYSPARA_H

#undef QT_NO_DEBUG_OUTPUT
/* 系统错误码定义
 * 1000~1999 系统错误
 * 2000~2999 数据库错误
 * 3000~ 应用错误
 */

#define ERR_SYS             1000
#define ERR_INIT            1001
#define ERR_CONF_NOTFUND    1010
#define ERR_CONF_ARGERR     1011
#define ERR_CONF            1012

#define ERR_DB              2000

/* 基本数据长度定义 */
#define CONF_FILE_MAXLEN    128
#define USER_ID_MAXLEN      16
#define PASSWD_MAXLEN       16
#define PASSWD_MINLEN       6

/* 全局数据定义*/
static char conf_file[CONF_FILE_MAXLEN]="~/rmtconf1.ini";




#endif // RMTSYSPARA_H
