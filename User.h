#ifndef _USER_H_
#define _USER_H_
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#pragma once
using namespace std;
class User {
    private:
        int userid;  //用户编号
	    string username;  //用户名
	    string password;  //密码
        string usertype;
    public:
        User *next;  //用于链表
        User() = default;
        ~User() = default;
        void change_password();  //修改用户密码
        friend class UserDataController;  //设置友元类，便于管理数据
        string get_password();
        string getname();
        string get_usertype();
        int getid();
        static void printtitle();
        friend ostream & operator << (ostream &, User &);
};

#endif
