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
        void file_read() override;  //��ȡ�ļ��е���Ϣ��������
        void file_write() override;  //�������е���Ϣд���ļ���
    public: 
        GoodsDataController();
        ~GoodsDataController();
        void add_info(OperationRecorder &, string);  //����µĻ�����Ϣ
        void delete_info(OperationRecorder &, string);  //ɾ���Ѿ����ڵĻ�����Ϣ
        virtual void show_list() const override;  //��ʾ���л������Ϣ
        void modify_goodsinfo(OperationRecorder &, string);  //�޸��Ѿ����ڵĻ�����Ϣ
        void query_goodsinfo();  //��ѯ������Ϣ
        Goods* find_goods(const string) const;  //�û������Բ�ѯ�����ڽ������û�ʱ������
        Goods* find_goods_id(const int id) const;
};
#endif