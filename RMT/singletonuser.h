#ifndef SINGLETONUSER_H
#define SINGLETONUSER_H

#include <string>
/*
 * 单例模式声明用户结构体
 */

class SingletonUser
{




public:
    static SingletonUser* getInstance();

private:
    char user_id[12+1];
    char user_name[128+1];
    char user_pwd[16+1];


    static SingletonUser* instance;
    SingletonUser();

    SingletonUser(const SingletonUser&);
    SingletonUser& operator=(const SingletonUser&);

};

#endif // SINGLETONUSER_H
