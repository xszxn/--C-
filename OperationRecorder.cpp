#include "OperationRecorder.h"
const char* filename2 = "RecorderData.txt";			//记录信息文件
OperationRecorder::OperationRecorder() {  //记录链表的初始化，建立头结点,并从文件中读取信息建立链表
    head = new Recordnode;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename2);
    if(!ifs) {  //如果文件不存在
        recordcnt = 0;  //初始化编号
        file_write();  //建立文件
    }
    else {
        ifs.close();
        file_read();
    }
}

OperationRecorder::~OperationRecorder() {
    file_write();
    Recordnode *p = head->next, *q;
    while(p!=NULL) {
        q = p;
        p = p->next;
        delete q;
    }
    delete head;
}

void OperationRecorder::file_read() {
    ifstream ifs(filename2);
    if(!ifs) {  //文件打开失败
        cout<<"<<    文件打开失败"<<endl;
        exit(0); 
    }
    ifs >> recordcnt;
    Recordnode *q = head;
    int i = 0;
    while(i < recordcnt) {	
        Recordnode *p = new Recordnode;
        ifs >> p->nodeid >> p->opusername;
        ifs >> p->data.first.goodsid >> p->data.first.goodsname >> p->data.first.price >> p->data.first.count;
        ifs >> p->data.second.goodsid >> p->data.second.goodsname >> p->data.second.price >> p->data.second.count;
        tail = p;
        q->next = p;
        p->next = NULL;
        q = p;
        i ++;
    }
    ifs.close();
}

void OperationRecorder::file_write() {  //通过文件的读写将链表中的内容写到文件中
    Recordnode *p = head->next;
    ofstream ofs(filename2);
    if(!ofs) {
        cout<<"<<    文件打开失败"<<endl;
        exit(0);
    }
    ofs << recordcnt << endl;  //将记录编号写入文件第一行
    while(p != NULL) {
        ofs << p->nodeid << " " << p->opusername << endl;
        ofs << p->data.first.goodsid << " " << p->data.first.goodsname << " " << p->data.first.price << " " << p->data.first.count << endl;
        ofs << p->data.second.goodsid << " " << p->data.second.goodsname << " " << p->data.second.price << " " << p->data.second.count << endl;
        p = p->next;
    }
    ofs.close();
}

void OperationRecorder::add_recordinfo(Goods &a , Goods &b, string &name) {
    recordcnt ++;  //编号++
    Recordnode *p = new Recordnode;
    p->nodeid = recordcnt;
	p->data.first = a;
    p->data.second = b;
    p->opusername = name;
    p->next = NULL;  
    tail->next = p;
    tail = p;
}

void OperationRecorder::show_list() const {
    Recordnode *p = head->next;
    cout << "<<    共查询到" << recordcnt << "个记录" << endl;
    cout << "<<    " << std::left << setw(10) << "编号" << std::left << setw(15) << "货物编号" << std::left << setw(15) << "货物名称" << std::left << setw(15) 
         << "货物单价" << std::left << setw(15) << "货物数量" << std::left << setw(15) << "货物总价" << std::left << setw(15) << "操作用户" << endl;
    while(p != NULL) {
        cout << "<<    " << std::left << setw(10) << p->nodeid << std::left << setw(15) << p->data.first.goodsid << std::left << setw(15) << p->data.first.goodsname << std::left << setw(15)
        << p->data.first.price << std::left << setw(15) << p->data.first.count << std::left << setw(15) << p->data.first.count * p->data.first.price << std::left << setw(15) << p->opusername << endl;
        if(p->data.second.goodsid == 0) {
            cout << "<<            |-新增货物"<< endl;
        }
        else if(p->data.second.goodsid == -1){
            cout << "<<            |-删除货物"<< endl;
        }
        else if(p->data.first - p->data.second){
            cout << "<<    " << std::left << setw(8) << " " << std::left << setw(17) << "->修改后" << std::left << setw(15) << " " << std::left << setw(15)
        << p->data.second.price << std::left << setw(15) << p->data.second.count << std::left << setw(15) << p->data.second.count * p->data.second.price << endl;
        }
        cout << "<<    ----------------------------------------------------------------------------------------------" <<endl;
        p = p->next;
    }
    return;
}