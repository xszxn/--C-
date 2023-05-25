#ifndef _GOODSDATACONTROLLER_H_
#define _GOODSDATACONTROLLER_H_
#include "Goods.h"
#include "Sorter.h"
#include "DataController.h"
#include "OperationRecorder.h"
class GoodsDataController : public DataController{
    private:
        int goodsnum;
        int goodscnt;
        Goods *head;
        Goods *tail;
        void file_read() override;  //读取文件中的信息建立链表
        void file_write() override;  //将链表中的信息写到文件中
    public: 
        GoodsDataController();
        ~GoodsDataController();
        void add_info(OperationRecorder &, string);  //添加新的货物信息
        void delete_info(OperationRecorder &, string);  //删除已经存在的货物信息
        virtual void show_list() const override;  //显示所有货物的信息
        void modify_goodsinfo(OperationRecorder &, string);  //修改已经存在的货物信息
        void query_goodsinfo();  //查询货物信息
        Goods* find_goods(const string) const;  //用户存在性查询，用于建立新用户时判重名
        Goods* find_goods_id(const int id) const;
};
#endif