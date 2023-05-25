#ifndef OPERATIONRECORDER_H
#define OPERATIONRECORDER_H
#include "Goods.h"
#include "DataController.h"
#include<string>
struct Recordnode{
    pair<Goods, Goods> data;   //data用户记录goods元素修改前后的数据
    int nodeid;
    string opusername;
    Recordnode* next;
};
class OperationRecorder : public DataController{
    private:
        int recordcnt;
        Recordnode *head;
        Recordnode *tail;
        virtual void file_read() override;  //读取文件中的信息建立链表
        virtual void file_write() override;  //将链表中的信息写到文件中
    public:
        OperationRecorder();  //构造函数，完成信息链表的初始化
        ~OperationRecorder();  //析构函数，删除信息链表所占的内存空间
        void add_recordinfo(Goods & , Goods &, string &);  //添加新的记录信息
        virtual void show_list() const override;  //显示所有记录的信息
};
#endif