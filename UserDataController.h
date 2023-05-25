#ifndef _USERDATACONTROLLER_H_
#define _USERDATACONTROLLER_H_
#include "User.h"
#include "DataController.h"
class UserDataController : public DataController{
    private:
        int usercnt;
        int usernum;
        User *head;
        User *tail;
        virtual void file_read() override;  //读取文件中的信息建立链表
        virtual void file_write() override;  //将链表中的信息写到文件中
    public:
        UserDataController();  //构造函数，完成用户信息链表的初始化
        ~UserDataController();  //析构函数，删除用户信息链表所占的内存空间
        void add_info();  //插入新的用户信息
        void delete_info();  //删除已经存在的用户信息
        virtual void show_list() const override;  //显示所有用户的信息
        bool login_success(User*, const string) const;  //验证用户的登入信息
        User* find_user(const string) const;  //用户存在性查询
        friend class Admin;
};
#endif