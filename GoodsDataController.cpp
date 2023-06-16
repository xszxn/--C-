#include "GoodsDataController.h"
const char* filename1 = "GoodsData.txt";			//������Ϣ�ļ�
GoodsDataController::GoodsDataController() {  //�û�����ĳ�ʼ��������ͷ���,�����ļ��ж�ȡ��Ϣ��������
    head = new Goods;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename1);
    if(!ifs) {  //����ļ�������
        goodscnt = 0;  //��ʼ�����
        goodsnum = 0;  //��ʼ������
        file_write();  //�����ļ�
    }
    else {
        ifs.close();
        file_read();
    }
}

GoodsDataController::~GoodsDataController() {
    file_write();
    Goods *p = head->next, *q;
    while(p!=NULL) {
        q = p;
        p = p->next;
        delete q;
    }
    delete head;
}

void GoodsDataController::file_read() {
    ifstream ifs(filename1);
    if(!ifs) {  //�ļ���ʧ��
        cout<<"<<    �ļ���ʧ��"<<endl;
        exit(0); 
    }
    ifs >> goodscnt >> goodsnum;
    Goods *q = head;
    int i = 0;
    while(i < goodsnum) {	
        Goods *p = new Goods;
        ifs >> p->goodsid >> p->goodsname >> p->price >> p->count;
        tail = p;
        q->next = p;
        p->next = NULL;
        q = p;
        i ++;
    }
    ifs.close();
}

void GoodsDataController::file_write() {  //ͨ���ļ��Ķ�д�������е�����д���ļ���
    Goods *p = head->next;
    ofstream ofs(filename1);
    if(!ofs) {
        cout<<"<<    �ļ���ʧ��"<<endl;
        exit(0);
    }
    ofs << goodscnt << endl << goodsnum << endl;  //����ź��û���д���ļ�ͷ����
    while(p != NULL) {
        ofs << p->goodsid << " " << p->goodsname << " " << p->price << " " << p->count << endl;
        p = p->next;
    }
    ofs.close();
}

void GoodsDataController::add_info(OperationRecorder &recorder, string name) {
    goodscnt ++;  //���++
    Goods *p = new Goods;
    p->goodsid = goodscnt;
	cout  << "<<    �������ӡ�"  <<  endl;
    cout << "<<" << endl;
	cout  << ">>    ��    �����������   �";
    cin >> p->goodsname;
    while(find_goods(p->goodsname) != NULL) {  //�жϻ������Ƿ��ظ������ظ�����Ҫ���´���
        cout << "<<    warning:�û������Ѿ����ڣ����������룡" << endl;
        cout << ">>    ��    �����������   �";
        cin >> p->goodsname;
    }
    cout << ">>    ��   ��������ﵥ��  �";
    cin >> p->price;
    cout << ">>    ��   �������������  �";
    cin >> p->count;
    p->next = NULL;  //���û���Ϊͷ�ڵ�
    tail->next = p;
    tail = p;
    goodsnum ++;  //�û���++
    Goods cpy = *p;
    cpy.goodsid = 0;  //�ڶ�����0�����������ӻ���ʵ�¼�
    recorder.add_recordinfo(*p, cpy, name);  //�����¼��������޸ļ�¼
	cout << "<<" << endl;
    cout << "<<    ��  ���ﴴ���ɹ���  ��" << endl;
}

void GoodsDataController::delete_info(OperationRecorder &recorder, string name) {
	cout << "<<    �����ɾ����"  <<  endl;
	cout << "<<" << endl;
	cout << ">>    ��    �����������  �"; 
    string tmp_goodsname;  //������ʱ���û�������
    cin >> tmp_goodsname;
    bool delete_success = false;
    Goods *t = head, *u; 
    while(t->next != NULL) {
        u = t->next;
        if(u->goodsname == tmp_goodsname) {
            Goods *de = u;
            Goods cpy = *de;
            cpy.goodsid = -1;  //�ڶ�����-1��������ɾ������ʵ�¼�
            recorder.add_recordinfo(*de, cpy, name);  //�����¼��������޸ļ�¼
            t->next = t->next->next;
            goodsnum --;
            if(u -> next == NULL) tail = t;
            delete de;  //�ͷ�ɾ������Ŀռ�
            delete_success = true;  //��ǳɹ�ɾ��
        }
        t = u;
    } 
    if(delete_success == false) {  //δ�ɹ�ɾ��
        cout << "<<    ��   δ��ѯ�������� ��" << endl; 
	    cout << "<<" << endl;
        return;
    }
    else {
        cout << "<<    ��   �ɹ�ɾ������  �"<< tmp_goodsname << endl; 
        cout << "<<" << endl;
    }
}

Goods* GoodsDataController::find_goods(const string goodsname) const {
    Goods *p = head->next;
    while(p != NULL) {
        if(p -> goodsname == goodsname) return p;  //���ز�ѯ����
        p=p->next;
    }
    return NULL;  //����δ��ѯ��
}

Goods* GoodsDataController::find_goods_id(const int id) const {
    Goods *p = head->next;
    while(p != NULL) {
        if(p -> goodsid == id) return p;  //���ز�ѯ����
        p=p->next;
    }
    return NULL;  //����δ��ѯ��
}

void GoodsDataController::modify_goodsinfo(OperationRecorder &recorder, string name) {
    cout << "<<    ������ѯ��"  <<  endl;
    cout << "<<" << endl;
    cout << "<<    ��    ����ѡ���ѯ��ʽ  �" << endl; 
    cout << "<<      1.�����Ų�ѯ      " << endl;
    cout << "<<      2.�������Ʋ�ѯ      " << endl;
    cout << "<<      0.���ز˵�          " << endl;
    cout << "<<" << endl;
    char t;
    cout << ">>    �ȴ����룺" ;
    cin >> t;
    string goodsname;
    int goodsid;
    Goods *p = NULL;
    Goods cpy;
    if(t == '2') {
        cout  <<  ">>    ��    �����������  �"; 
        cin >> goodsname;
        p = find_goods(goodsname);
        if(p == NULL) {
            cout  <<  "<<    ��   δ��ѯ�������� ��" << endl; 
            cout << "<<" << endl;
            return;
        }
        cout << "<< " << endl;
        cout << "<<    ��   �ɹ��ҵ�����  �"<< p->goodsname << endl;
        cout << "<<    ��     ������    �"<< p->goodsid << endl;
        cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
        cout << "<<    ��     ��������    �"<< p->count << endl;
        cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
        cout << "<<" << endl;
    } 
    else if(t == '1') {
        cout  <<  ">>    ��   ����������� �"; 
        cin >> goodsid;
        p = find_goods_id(goodsid);
        if(p == NULL) {
            cout  <<  "<<    �� δ��ѯ�������� ��" << endl; 
            cout << "<<" << endl;
            return;
        }
        cout << "<< " << endl;
        cout << "<<    ��   �ɹ��ҵ�����  �"<< p->goodsname << endl;
        cout << "<<    ��     ������    �"<< p->goodsid << endl;
        cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
        cout << "<<    ��     ��������    �"<< p->count << endl;
        cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
        cout << "<<" << endl;
    }
    else {
        if(t != '0')
        cout  <<  "<<    �� �����쳣������ ��" << endl; 
        cout << "<<" << endl;
        return;
    }
    cpy = *p;
    cout << "<<    ��    ��ѡ���޸ķ�ʽ  �" << endl; 
    cout << "<<      1.�޸Ļ��ﵥ��      " << endl;
    cout << "<<      2.�������      " << endl;
    cout << "<<      3.�������      " << endl;
    cout << "<<      0.���ز˵�          " << endl;
    cout << "<<" << endl;
    cout << ">>    �ȴ����룺" ;
    cin >> t;
    int num;
    switch(t) {
        case '1':
            cout  <<  ">>    ��   �������޸ĺ�Ļ��ﵥ�� �";
            cin >> p->price;
            if(cpy-(*p)){
                cout << "<<    ��     �ɹ��޸�    ��"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ��     ��Ч�޸�    ��" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ��   �޸ĺ�Ļ���  �"<< p->goodsname << endl;
            cout << "<<    ��     ������    �"<< p->goodsid << endl;
            cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
            cout << "<<    ��     ��������    �"<< p->count << endl;
            cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '2':
            cout  <<  ">>    ��   ����������������� �";
            cin >> num;
            p->count += num;
            if(cpy-(*p)){
                cout << "<<    ��     �ɹ��޸�    ��"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ��     ��Ч�޸�    ��" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ��   �޸ĺ�Ļ���  �"<< p->goodsname << endl;
            cout << "<<    ��     ������    �"<< p->goodsid << endl;
            cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
            cout << "<<    ��     ��������    �"<< p->count << endl;
            cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '3':
            cout  <<  ">>    ��   ����������³������ �";
            cin >> num;
            if(p->count < num) {
                cout  <<  "<<    ��     �ɹ�ʧ�ܣ������治��    ��"<< endl;
                break;
            }
            p->count -= num;
            if(cpy-(*p)){
                cout << "<<    ��     �ɹ��޸�    ��"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ��     ��Ч�޸�    ��" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ��   �޸ĺ�Ļ���  �"<< p->goodsname << endl;
            cout << "<<    ��     ������    �"<< p->goodsid << endl;
            cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
            cout << "<<    ��     ��������    �"<< p->count << endl;
            cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        default:
            break;
    }
    return;
}

void GoodsDataController::query_goodsinfo() {
    cout << "<<    ������ѯ��"  <<  endl;
    cout << "<<" << endl;
    cout << "<<    ��    ����ѡ���ѯ��ʽ  �" << endl; 
    cout << "<<      1.�����Ų�ѯ      " << endl;
    cout << "<<      2.�������Ʋ�ѯ      " << endl;
    cout << "<<      3.���ջ��ﵥ��ɸѡ��ѯ      " << endl;
    cout << "<<      4.���ջ�������ɸѡ��ѯ      " << endl;
    cout << "<<      0.���ز˵�          " << endl;
    cout << "<<" << endl;
    char t;
    cout << ">>    �ȴ����룺" ;
    cin >> t;
    string goodsname;
    int goodsid;
    int g;
    Sorter u(head);
    Goods *p;
    switch(t) {
        case '1':
            cout  <<  ">>    ��    �����������  �"; 
            cout << "<<" << endl;
            cin >> goodsid;
            p = find_goods_id(goodsid);
            if(p == NULL) {
                cout  <<  "<<    ��   δ��ѯ�������� ��" << endl; 
	            cout << "<<" << endl;
                return;
            }
            cout << "<<    ��   �ɹ��ҵ�����  �"<< p->goodsname << endl;
            cout << "<<    ��     ������    �"<< p->goodsid << endl;
            cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
            cout << "<<    ��     ��������    �"<< p->count << endl;
            cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '2':
            cout  <<  ">>    ��    �����������  �"; 
            cin >> goodsname;
            p = find_goods(goodsname);
            if(p == NULL) {
                cout << "<<    ��   δ��ѯ�������� ��" << endl; 
            	cout << "<<" << endl;
                return;
            }
            cout << "<<    ��   �ɹ��ҵ�����  �"<< p->goodsname << endl;
            cout << "<<    ��     ������    �"<< p->goodsid << endl;
            cout << "<<    ��     ���ﵥ��    �"<< p->price << endl;
            cout << "<<    ��     ��������    �"<< p->count << endl;
            cout << "<<    ��     �����ܼ�    �"<< p->price * p->count << endl;
        	cout << "<<" << endl;
            break;
        case '3':
            cout << "<<    ��    ����ѡ��ɸѡ��ʽ  �" << endl; 
            cout << "<<      1.����      " << endl;
            cout << "<<      2.����      " << endl;
            cout << "<<      3.ѡ������      " << endl;
            cout << "<<" << endl;
            cout << ">>    �ȴ����룺" ;
            cin >> g;
            if(g == 1 || g == 2 || g == 3) {
                u.filter_price(g);
            }
            else {
                cout  <<  "<<    ��   ѡ���������֣� ��" << endl; 
            }
            break;
        case '4':
            cout << "<<    ��    ����ѡ��ɸѡ��ʽ  �" << endl; 
            cout << "<<      1.����      " << endl;
            cout << "<<      2.����      " << endl;
            cout << "<<      3.ѡ������      " << endl;
            cout << "<<" << endl;
            cout << ">>    �ȴ����룺" ;
            cin >> g;
            if(g == 1 || g == 2 || g == 3) {
                u.filter_count(g);
            }
            else {
                cout << "<<    ��   ѡ���������֣� ��" << endl; 
            }
            break;
        case '0':
            break;
        default:
            cout << "<<    ��   ѡ���������֣� ��" << endl; 
            break;
    } 
}

void GoodsDataController::show_list() const {
    Sorter u(head);
    cout << "<<    ��    ����ѡ������ʽ  �" << endl; 
    cout << "<<      1.���ջ���������      " << endl;
    cout << "<<      2.���ջ��ﵥ������      " << endl;
    cout << "<<      3.���ջ�����������      " << endl;
    cout << "<<      4.���ջ����ܼ�����      " << endl;
    cout << "<<      0.���ز˵�          " << endl;
    char t;
    cout << "<< " <<endl;
    cout << ">>    �ȴ����룺" ;
    cin >> t;
    if(t == '1' || t == '2' || t == '3' || t == '4') {
        cout << "<<    ��    ����ѡ������˳��  �" << endl; 
        cout << "<<      1.������������      " << endl;
        cout << "<<      2.���ս�������      " << endl;
        cout << "<<      0.���ز˵�          " << endl;
    }
    else if (t == '0') {
        return;
    }
    else {
        cout << "<<    ������󣡼����������˵�" << endl;
        return;
    }
    char k;
    cout << "<< " <<endl;
    cout << ">>    �ȴ����룺" ;
    cin >> k;
    if(k == '1') {
        switch(t) { 
            case '1': 
                u.sortBy(cmp_by_id_up);  //id,��������
                u.print();
                break;
            case '2':
                u.sortBy(cmp_by_price_up);  //�۸�,��������
                u.print();
                break;
            case '3':
                u.sortBy(cmp_by_count_up);  //����,��������
                u.print();
                break;
            case '4':
                u.sortBy(cmp_by_sumprice_up);  //�ܼ�,��������
                u.print();
                break;
            default:
                break;
        }
    }
    else if(k == '2') {
        switch(t) { 
            case '1': 
                u.sortBy(cmp_by_id_down);  //id,��������
                u.print();
                break;
            case '2':
                u.sortBy(cmp_by_price_down);  //�۸�,��������
                u.print();
                break;
            case '3':
                u.sortBy(cmp_by_count_down);  //����,��������
                u.print();
                break;
            case '4':
                u.sortBy(cmp_by_sumprice_down);  //�ܼ�,��������
                u.print();
                break;
            default:
                break;
        }
    }
    else {
        cout << "<<    ������󣡼����������˵�" << endl;
    }
    return;
}


