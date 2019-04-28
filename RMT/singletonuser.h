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

/*
create table rmt_user(
user_id char(12) not null,
user_name varchar(128),
user_pwd char(16) not null,
user_level int(1) not null,
department_id int(3) not null,
team_id int(3)
);

create table rmt_map(
map_type char(2) not null,
map_stat char(2) not null,
map_id int(3) not null,
map_name varchar(512) not null
);

*/

#endif // SINGLETONUSER_H
