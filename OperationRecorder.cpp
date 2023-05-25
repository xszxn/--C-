#include "OperationRecorder.h"
const char* filename2 = "RecorderData.txt";			//��¼��Ϣ�ļ�
OperationRecorder::OperationRecorder() {  //��¼����ĳ�ʼ��������ͷ���,�����ļ��ж�ȡ��Ϣ��������
    head = new Recordnode;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename2);
    if(!ifs) {  //����ļ�������
        recordcnt = 0;  //��ʼ�����
        file_write();  //�����ļ�
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
    if(!ifs) {  //�ļ���ʧ��
        cout<<"<<    �ļ���ʧ��"<<endl;
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

void OperationRecorder::file_write() {  //ͨ���ļ��Ķ�д�������е�����д���ļ���
    Recordnode *p = head->next;
    ofstream ofs(filename2);
    if(!ofs) {
        cout<<"<<    �ļ���ʧ��"<<endl;
        exit(0);
    }
    ofs << recordcnt << endl;  //����¼���д���ļ���һ��
    while(p != NULL) {
        ofs << p->nodeid << " " << p->opusername << endl;
        ofs << p->data.first.goodsid << " " << p->data.first.goodsname << " " << p->data.first.price << " " << p->data.first.count << endl;
        ofs << p->data.second.goodsid << " " << p->data.second.goodsname << " " << p->data.second.price << " " << p->data.second.count << endl;
        p = p->next;
    }
    ofs.close();
}

void OperationRecorder::add_recordinfo(Goods &a , Goods &b, string &name) {
    recordcnt ++;  //���++
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
    cout << "<<    ����ѯ��" << recordcnt << "����¼" << endl;
    cout << "<<    " << std::left << setw(10) << "���" << std::left << setw(15) << "������" << std::left << setw(15) << "��������" << std::left << setw(15) 
         << "���ﵥ��" << std::left << setw(15) << "��������" << std::left << setw(15) << "�����ܼ�" << std::left << setw(15) << "�����û�" << endl;
    while(p != NULL) {
        cout << "<<    " << std::left << setw(10) << p->nodeid << std::left << setw(15) << p->data.first.goodsid << std::left << setw(15) << p->data.first.goodsname << std::left << setw(15)
        << p->data.first.price << std::left << setw(15) << p->data.first.count << std::left << setw(15) << p->data.first.count * p->data.first.price << std::left << setw(15) << p->opusername << endl;
        if(p->data.second.goodsid == 0) {
            cout << "<<            |-��������"<< endl;
        }
        else if(p->data.second.goodsid == -1){
            cout << "<<            |-ɾ������"<< endl;
        }
        else if(p->data.first - p->data.second){
            cout << "<<    " << std::left << setw(8) << " " << std::left << setw(17) << "->�޸ĺ�" << std::left << setw(15) << " " << std::left << setw(15)
        << p->data.second.price << std::left << setw(15) << p->data.second.count << std::left << setw(15) << p->data.second.count * p->data.second.price << endl;
        }
        cout << "<<    ----------------------------------------------------------------------------------------------" <<endl;
        p = p->next;
    }
    return;
}