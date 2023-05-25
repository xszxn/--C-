#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H
class DataController {
    public:
        virtual void file_read() = 0;  //读取文件中的信息建立链表
        virtual void file_write() = 0;  //将链表中的信息写到文件中
        virtual void show_list() const = 0;  //展示链表中的所有信息
};
#endif