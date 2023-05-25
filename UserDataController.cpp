#include "UserDataController.h"
const char* filename = "UserData.txt";			//用户信息文件
UserDataController::UserDataController() {  //用户链表的初始化，建立头结点,并从文件中读取信息建立链表
    head = new User;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename);
    if(!ifs) {  //如果文件不存在
        usercnt = 0;  //初始化编号
        usernum = 0;  //初始化人数
        file_write();  //建立文件
    }
    else {
        ifs.close();
        file_read();
    }
}

UserDataController::~UserDataController() {
    file_write();
    User *p = head->next, *q;
    while(p!=NULL) {
        q = p;
        p = p->next;
        delete q;
    }
    delete head;
}

void UserDataController::file_read() {
    ifstream ifs(filename);
    if(!ifs) {  //文件打开失败
        cout<<"<<    文件打开失败"<<endl;
        exit(0); 
    }
    ifs >> usercnt >> usernum;
    User *q = head;
    int i = 0;
    while(i < usernum) {
        User *p = new User;
        tail = p;
        ifs >> p->userid >> p->username >> p->password >> p->usertype;
        q->next = p;
        p->next = NULL;
        q = p;
        i ++;
    }
    ifs.close();
}

void UserDataController::file_write() {  //通过文件的读写将链表中的内容写到文件中
    User *p = head->next;
    ofstream ofs(filename);
    if(!ofs) {
        cout<<"<<    文件打开失败"<<endl;
        exit(0);
    }
    ofs << usercnt << endl << usernum << endl;  //将编号和用户数写入文件头两行
    while(p != NULL) {
        ofs << p->userid << " " << p->username << " " << p->password << " " << p->usertype <<endl;
        p=p->next;
    }
    ofs.close();
}

void UserDataController::add_info() {
    usercnt ++;  //编号++
    User *p = new User;
    p->userid = usercnt;
	cout << "<<    ☆用户添加☆"  <<  endl;
	cout << "<<"  <<  endl;
	cout << ">>    ★    请输入用户名  ★：";
    cin >> p->username;
    while(find_user(p->username) != NULL) {  //判断用户名是否重复，若重复，需要重新创建
        cout << "<<    warning:该用户名已经存在，请重新输入！" << endl;
        cout << ">>    ★    请输入用户名  ★：";
        cin >> p->username;
    }
    cout << ">>    ★  请输入用户密码  ★：";
    cin >> p->password;
	cout << "<<" << endl;
    p->usertype = "user";
    p->next = NULL;  
    tail->next = p;
    tail = p;
    usernum ++;  //用户数++
    cout << "<<    ★  用户创建成功！  ★" << endl;
}

void UserDataController::delete_info() {
	cout << "<<    ☆用户删除☆"  <<  endl;
	cout << "<<"  <<  endl;
	cout << ">>    ★    请输入用户名  ★："; 
    string tmp_username;  //创建临时的用户名变量
    cin >> tmp_username;
    bool delete_success = false;
    User *t = head, *u; 
    while(t->next != NULL) {
        u = t->next;
        if(u->username == tmp_username) {
            if(u->usertype == "admin"){
                cout << "<<    ★   当前用户为管理员用户，无法删除！ ★" << endl; 
                cout << "<<"  <<  endl;
                return;
            }
            User *de = u;
            t->next = t->next->next;
            if(u -> next == NULL) tail = t;
            usernum --;
            delete de;  //释放删除用户的空间
            delete_success = true;
        }
        t = u;
    } 
    if(delete_success == false) {
        cout << "<<    ★   未查询到用户名 ★" << endl; 
        cout << "<<" << endl;
        return;
    }
    else {
        cout << "<<    ★   成功删除用户  ★："<< tmp_username << endl; 
        cout << "<<" << endl;
    }
}

User* UserDataController::find_user(const string username) const {
    User *p = head->next;
    while(p != NULL) {
        if(p -> username == username) return p;  //返回查询到了
        p = p->next;
    }
    return NULL;  //返回未查询到
}

bool UserDataController::login_success(User *p, const string password) const {
    if(p->get_password() == password) return true;
    return false;
}

void UserDataController::show_list() const {
    User *p = head->next;
    User::printtitle();
    while(p != NULL) {
        cout << *p;
        p = p->next;
    }
    return;
}