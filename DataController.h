#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H
class DataController {
    public:
        virtual void file_read() = 0;  //��ȡ�ļ��е���Ϣ��������
        virtual void file_write() = 0;  //�������е���Ϣд���ļ���
        virtual void show_list() const = 0;  //չʾ�����е�������Ϣ
};
#endif