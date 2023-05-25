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
        int userid;  //�û����
	    string username;  //�û���
	    string password;  //����
        string usertype;
    public:
        User *next;  //��������
        User() = default;
        ~User() = default;
        void change_password();  //�޸��û�����
        friend class UserDataController;  //������Ԫ�࣬���ڹ�������
        string get_password();
        string getname();
        string get_usertype();
        int getid();
        static void printtitle();
        friend ostream & operator << (ostream &, User &);
};

#endif
