#ifndef OPERATIONRECORDER_H
#define OPERATIONRECORDER_H
#include "Goods.h"
#include "DataController.h"
#include<string>
struct Recordnode{
    pair<Goods, Goods> data;   //data�û���¼goodsԪ���޸�ǰ�������
    int nodeid;
    string opusername;
    Recordnode* next;
};
class OperationRecorder : public DataController{
    private:
        int recordcnt;
        Recordnode *head;
        Recordnode *tail;
        virtual void file_read() override;  //��ȡ�ļ��е���Ϣ��������
        virtual void file_write() override;  //�������е���Ϣд���ļ���
    public:
        OperationRecorder();  //���캯���������Ϣ����ĳ�ʼ��
        ~OperationRecorder();  //����������ɾ����Ϣ������ռ���ڴ�ռ�
        void add_recordinfo(Goods & , Goods &, string &);  //����µļ�¼��Ϣ
        virtual void show_list() const override;  //��ʾ���м�¼����Ϣ
};
#endif