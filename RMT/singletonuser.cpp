#include "singletonuser.h"

SingletonUser::SingletonUser(){

}

SingletonUser::SingletonUser(const SingletonUser&){

}


SingletonUser& SingletonUser::operator=(const SingletonUser&){

}


//在此处初始化
SingletonUser* SingletonUser::instance = new SingletonUser();

SingletonUser* SingletonUser::getInstance(){
    return instance;
}
