#include "GoodsDataController.h"
const char* filename1 = "GoodsData.txt";			//货物信息文件
GoodsDataController::GoodsDataController() {  //用户链表的初始化，建立头结点,并从文件中读取信息建立链表
    head = new Goods;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename1);
    if(!ifs) {  //如果文件不存在
        goodscnt = 0;  //初始化编号
        goodsnum = 0;  //初始化人数
        file_write();  //建立文件
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
    if(!ifs) {  //文件打开失败
        cout<<"<<    文件打开失败"<<endl;
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

void GoodsDataController::file_write() {  //通过文件的读写将链表中的内容写到文件中
    Goods *p = head->next;
    ofstream ofs(filename1);
    if(!ofs) {
        cout<<"<<    文件打开失败"<<endl;
        exit(0);
    }
    ofs << goodscnt << endl << goodsnum << endl;  //将编号和用户数写入文件头两行
    while(p != NULL) {
        ofs << p->goodsid << " " << p->goodsname << " " << p->price << " " << p->count << endl;
        p = p->next;
    }
    ofs.close();
}

void GoodsDataController::add_info(OperationRecorder &recorder, string name) {
    goodscnt ++;  //编号++
    Goods *p = new Goods;
    p->goodsid = goodscnt;
	cout  << "<<    ☆货物添加☆"  <<  endl;
    cout << "<<" << endl;
	cout  << ">>    ★    请输入货物名   ★：";
    cin >> p->goodsname;
    while(find_goods(p->goodsname) != NULL) {  //判断货物名是否重复，若重复，需要重新创建
        cout << "<<    warning:该货物名已经存在，请重新输入！" << endl;
        cout << ">>    ★    请输入货物名   ★：";
        cin >> p->goodsname;
    }
    cout << ">>    ★   请输入货物单价  ★：";
    cin >> p->price;
    cout << ">>    ★   请输入货物数量  ★：";
    cin >> p->count;
    p->next = NULL;  //新用户成为头节点
    tail->next = p;
    tail = p;
    goodsnum ++;  //用户数++
    Goods cpy = *p;
    cpy.goodsid = 0;  //第二项置0，表明是增加货物实事件
    recorder.add_recordinfo(*p, cpy, name);  //监听事件，增加修改记录
	cout << "<<" << endl;
    cout << "<<    ★  货物创建成功！  ★" << endl;
}

void GoodsDataController::delete_info(OperationRecorder &recorder, string name) {
	cout << "<<    ☆货物删除☆"  <<  endl;
	cout << "<<" << endl;
	cout << ">>    ★    请输入货物名  ★："; 
    string tmp_goodsname;  //创建临时的用户名变量
    cin >> tmp_goodsname;
    bool delete_success = false;
    Goods *t = head, *u; 
    while(t->next != NULL) {
        u = t->next;
        if(u->goodsname == tmp_goodsname) {
            Goods *de = u;
            Goods cpy = *de;
            cpy.goodsid = -1;  //第二项置-1，表明是删除货物实事件
            recorder.add_recordinfo(*de, cpy, name);  //监听事件，增加修改记录
            t->next = t->next->next;
            goodsnum --;
            if(u -> next == NULL) tail = t;
            delete de;  //释放删除货物的空间
            delete_success = true;  //标记成功删除
        }
        t = u;
    } 
    if(delete_success == false) {  //未成功删除
        cout << "<<    ★   未查询到货物名 ★" << endl; 
	    cout << "<<" << endl;
        return;
    }
    else {
        cout << "<<    ★   成功删除货物  ★："<< tmp_goodsname << endl; 
        cout << "<<" << endl;
    }
}

Goods* GoodsDataController::find_goods(const string goodsname) const {
    Goods *p = head->next;
    while(p != NULL) {
        if(p -> goodsname == goodsname) return p;  //返回查询到了
        p=p->next;
    }
    return NULL;  //返回未查询到
}

Goods* GoodsDataController::find_goods_id(const int id) const {
    Goods *p = head->next;
    while(p != NULL) {
        if(p -> goodsid == id) return p;  //返回查询到了
        p=p->next;
    }
    return NULL;  //返回未查询到
}

void GoodsDataController::modify_goodsinfo(OperationRecorder &recorder, string name) {
    cout << "<<    ☆货物查询☆"  <<  endl;
    cout << "<<" << endl;
    cout << "<<    ★    请输选择查询方式  ★：" << endl; 
    cout << "<<      1.货物编号查询      " << endl;
    cout << "<<      2.货物名称查询      " << endl;
    cout << "<<      0.返回菜单          " << endl;
    cout << "<<" << endl;
    char t;
    cout << ">>    等待输入：" ;
    cin >> t;
    string goodsname;
    int goodsid;
    Goods *p = NULL;
    Goods cpy;
    if(t == '2') {
        cout  <<  ">>    ★    请输入货物名  ★："; 
        cin >> goodsname;
        p = find_goods(goodsname);
        if(p == NULL) {
            cout  <<  "<<    ★   未查询到货物名 ★" << endl; 
            cout << "<<" << endl;
            return;
        }
        cout << "<< " << endl;
        cout << "<<    ★   成功找到货物  ★："<< p->goodsname << endl;
        cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
        cout << "<<    ★     货物单价    ★："<< p->price << endl;
        cout << "<<    ★     货物数量    ★："<< p->count << endl;
        cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
        cout << "<<" << endl;
    } 
    else if(t == '1') {
        cout  <<  ">>    ★   请输入货物编号 ★："; 
        cin >> goodsid;
        p = find_goods_id(goodsid);
        if(p == NULL) {
            cout  <<  "<<    ★ 未查询到货物编号 ★" << endl; 
            cout << "<<" << endl;
            return;
        }
        cout << "<< " << endl;
        cout << "<<    ★   成功找到货物  ★："<< p->goodsname << endl;
        cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
        cout << "<<    ★     货物单价    ★："<< p->price << endl;
        cout << "<<    ★     货物数量    ★："<< p->count << endl;
        cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
        cout << "<<" << endl;
    }
    else {
        if(t != '0')
        cout  <<  "<<    ★ 输入异常！！！ ★" << endl; 
        cout << "<<" << endl;
        return;
    }
    cpy = *p;
    cout << "<<    ★    请选择修改方式  ★：" << endl; 
    cout << "<<      1.修改货物单价      " << endl;
    cout << "<<      2.货物入库      " << endl;
    cout << "<<      3.货物出库      " << endl;
    cout << "<<      0.返回菜单          " << endl;
    cout << "<<" << endl;
    cout << ">>    等待输入：" ;
    cin >> t;
    int num;
    switch(t) {
        case '1':
            cout  <<  ">>    ★   请输入修改后的货物单价 ★：";
            cin >> p->price;
            if(cpy-(*p)){
                cout << "<<    ★     成功修改    ★"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ★     无效修改    ★" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ★   修改后的货物  ★："<< p->goodsname << endl;
            cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
            cout << "<<    ★     货物单价    ★："<< p->price << endl;
            cout << "<<    ★     货物数量    ★："<< p->count << endl;
            cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '2':
            cout  <<  ">>    ★   请输入货物新入库件数 ★：";
            cin >> num;
            p->count += num;
            if(cpy-(*p)){
                cout << "<<    ★     成功修改    ★"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ★     无效修改    ★" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ★   修改后的货物  ★："<< p->goodsname << endl;
            cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
            cout << "<<    ★     货物单价    ★："<< p->price << endl;
            cout << "<<    ★     货物数量    ★："<< p->count << endl;
            cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '3':
            cout  <<  ">>    ★   请输入货物新出库件数 ★：";
            cin >> num;
            if(p->count < num) {
                cout  <<  "<<    ★     成功失败：货物库存不足    ★"<< endl;
                break;
            }
            p->count -= num;
            if(cpy-(*p)){
                cout << "<<    ★     成功修改    ★"<< endl;
                recorder.add_recordinfo(cpy, *p, name);
            }
            else {
                cout << "<<    ★     无效修改    ★" << endl;
                break;
            }
            cout << "<<" << endl;
            cout << "<<    ★   修改后的货物  ★："<< p->goodsname << endl;
            cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
            cout << "<<    ★     货物单价    ★："<< p->price << endl;
            cout << "<<    ★     货物数量    ★："<< p->count << endl;
            cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        default:
            break;
    }
    return;
}

void GoodsDataController::query_goodsinfo() {
    cout << "<<    ☆货物查询☆"  <<  endl;
    cout << "<<" << endl;
    cout << "<<    ★    请输选择查询方式  ★：" << endl; 
    cout << "<<      1.货物编号查询      " << endl;
    cout << "<<      2.货物名称查询      " << endl;
    cout << "<<      3.按照货物单价筛选查询      " << endl;
    cout << "<<      4.按照货物数量筛选查询      " << endl;
    cout << "<<      0.返回菜单          " << endl;
    cout << "<<" << endl;
    char t;
    cout << ">>    等待输入：" ;
    cin >> t;
    string goodsname;
    int goodsid;
    int g;
    Sorter u(head);
    Goods *p;
    switch(t) {
        case '1':
            cout  <<  ">>    ★    请输入货物编号  ★："; 
            cout << "<<" << endl;
            cin >> goodsid;
            p = find_goods_id(goodsid);
            if(p == NULL) {
                cout  <<  "<<    ★   未查询到货物编号 ★" << endl; 
	            cout << "<<" << endl;
                return;
            }
            cout << "<<    ★   成功找到货物  ★："<< p->goodsname << endl;
            cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
            cout << "<<    ★     货物单价    ★："<< p->price << endl;
            cout << "<<    ★     货物数量    ★："<< p->count << endl;
            cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
            cout << "<<" << endl;
            break;
        case '2':
            cout  <<  ">>    ★    请输入货物名  ★："; 
            cin >> goodsname;
            p = find_goods(goodsname);
            if(p == NULL) {
                cout << "<<    ★   未查询到货物名 ★" << endl; 
            	cout << "<<" << endl;
                return;
            }
            cout << "<<    ★   成功找到货物  ★："<< p->goodsname << endl;
            cout << "<<    ★     货物编号    ★："<< p->goodsid << endl;
            cout << "<<    ★     货物单价    ★："<< p->price << endl;
            cout << "<<    ★     货物数量    ★："<< p->count << endl;
            cout << "<<    ★     货物总价    ★："<< p->price * p->count << endl;
        	cout << "<<" << endl;
            break;
        case '3':
            cout << "<<    ★    请输选择筛选方式  ★：" << endl; 
            cout << "<<      1.低于      " << endl;
            cout << "<<      2.高于      " << endl;
            cout << "<<      3.选择区间      " << endl;
            cout << "<<" << endl;
            cout << ">>    等待输入：" ;
            cin >> g;
            if(g == 1 || g == 2 || g == 3) {
                u.filter_price(g);
            }
            else {
                cout  <<  "<<    ★   选择错误的数字！ ★" << endl; 
            }
            break;
        case '4':
            cout << "<<    ★    请输选择筛选方式  ★：" << endl; 
            cout << "<<      1.低于      " << endl;
            cout << "<<      2.高于      " << endl;
            cout << "<<      3.选择区间      " << endl;
            cout << "<<" << endl;
            cout << ">>    等待输入：" ;
            cin >> g;
            if(g == 1 || g == 2 || g == 3) {
                u.filter_count(g);
            }
            else {
                cout << "<<    ★   选择错误的数字！ ★" << endl; 
            }
            break;
        case '0':
            break;
        default:
            cout << "<<    ★   选择错误的数字！ ★" << endl; 
            break;
    } 
}

void GoodsDataController::show_list() const {
    Sorter u(head);
    cout << "<<    ★    请输选择排序方式  ★：" << endl; 
    cout << "<<      1.按照货物编号排序      " << endl;
    cout << "<<      2.按照货物单价排序      " << endl;
    cout << "<<      3.按照货物数量排序      " << endl;
    cout << "<<      4.按照货物总价排序      " << endl;
    cout << "<<      0.返回菜单          " << endl;
    char t;
    cout << "<< " <<endl;
    cout << ">>    等待输入：" ;
    cin >> t;
    if(t == '1' || t == '2' || t == '3' || t == '4') {
        cout << "<<    ★    请输选择排序顺序  ★：" << endl; 
        cout << "<<      1.按照升序排序      " << endl;
        cout << "<<      2.按照降序排序      " << endl;
        cout << "<<      0.返回菜单          " << endl;
    }
    else if (t == '0') {
        return;
    }
    else {
        cout << "<<    输入错误！即将返回主菜单" << endl;
        return;
    }
    char k;
    cout << "<< " <<endl;
    cout << ">>    等待输入：" ;
    cin >> k;
    if(k == '1') {
        switch(t) { 
            case '1': 
                u.sortBy(cmp_by_id_up);  //id,升序排序
                u.print();
                break;
            case '2':
                u.sortBy(cmp_by_price_up);  //价格,升序排序
                u.print();
                break;
            case '3':
                u.sortBy(cmp_by_count_up);  //数量,升序排序
                u.print();
                break;
            case '4':
                u.sortBy(cmp_by_sumprice_up);  //总价,升序排序
                u.print();
                break;
            default:
                break;
        }
    }
    else if(k == '2') {
        switch(t) { 
            case '1': 
                u.sortBy(cmp_by_id_down);  //id,降序排序
                u.print();
                break;
            case '2':
                u.sortBy(cmp_by_price_down);  //价格,降序排序
                u.print();
                break;
            case '3':
                u.sortBy(cmp_by_count_down);  //数量,降序排序
                u.print();
                break;
            case '4':
                u.sortBy(cmp_by_sumprice_down);  //总价,降序排序
                u.print();
                break;
            default:
                break;
        }
    }
    else {
        cout << "<<    输入错误！即将返回主菜单" << endl;
    }
    return;
}


