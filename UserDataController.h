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
        virtual void file_read() override;  //��ȡ�ļ��е���Ϣ��������
        virtual void file_write() override;  //�������е���Ϣд���ļ���
    public:
        UserDataController();  //���캯��������û���Ϣ����ĳ�ʼ��
        ~UserDataController();  //����������ɾ���û���Ϣ������ռ���ڴ�ռ�
        void add_info();  //�����µ��û���Ϣ
        void delete_info();  //ɾ���Ѿ����ڵ��û���Ϣ
        virtual void show_list() const override;  //��ʾ�����û�����Ϣ
        bool login_success(User*, const string) const;  //��֤�û��ĵ�����Ϣ
        User* find_user(const string) const;  //�û������Բ�ѯ
        friend class Admin;
};
#endif