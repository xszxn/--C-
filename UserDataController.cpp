#include "UserDataController.h"
const char* filename = "UserData.txt";			//�û���Ϣ�ļ�
UserDataController::UserDataController() {  //�û�����ĳ�ʼ��������ͷ���,�����ļ��ж�ȡ��Ϣ��������
    head = new User;
    tail = head;
    head->next = NULL;
    ifstream ifs(filename);
    if(!ifs) {  //����ļ�������
        usercnt = 0;  //��ʼ�����
        usernum = 0;  //��ʼ������
        file_write();  //�����ļ�
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
    if(!ifs) {  //�ļ���ʧ��
        cout<<"<<    �ļ���ʧ��"<<endl;
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

void UserDataController::file_write() {  //ͨ���ļ��Ķ�д�������е�����д���ļ���
    User *p = head->next;
    ofstream ofs(filename);
    if(!ofs) {
        cout<<"<<    �ļ���ʧ��"<<endl;
        exit(0);
    }
    ofs << usercnt << endl << usernum << endl;  //����ź��û���д���ļ�ͷ����
    while(p != NULL) {
        ofs << p->userid << " " << p->username << " " << p->password << " " << p->usertype <<endl;
        p=p->next;
    }
    ofs.close();
}

void UserDataController::add_info() {
    usercnt ++;  //���++
    User *p = new User;
    p->userid = usercnt;
	cout << "<<    ���û���ӡ�"  <<  endl;
	cout << "<<"  <<  endl;
	cout << ">>    ��    �������û���  �";
    cin >> p->username;
    while(find_user(p->username) != NULL) {  //�ж��û����Ƿ��ظ������ظ�����Ҫ���´���
        cout << "<<    warning:���û����Ѿ����ڣ����������룡" << endl;
        cout << ">>    ��    �������û���  �";
        cin >> p->username;
    }
    cout << ">>    ��  �������û�����  �";
    cin >> p->password;
	cout << "<<" << endl;
    p->usertype = "user";
    p->next = NULL;  
    tail->next = p;
    tail = p;
    usernum ++;  //�û���++
    cout << "<<    ��  �û������ɹ���  ��" << endl;
}

void UserDataController::delete_info() {
	cout << "<<    ���û�ɾ����"  <<  endl;
	cout << "<<"  <<  endl;
	cout << ">>    ��    �������û���  �"; 
    string tmp_username;  //������ʱ���û�������
    cin >> tmp_username;
    bool delete_success = false;
    User *t = head, *u; 
    while(t->next != NULL) {
        u = t->next;
        if(u->username == tmp_username) {
            if(u->usertype == "admin"){
                cout << "<<    ��   ��ǰ�û�Ϊ����Ա�û����޷�ɾ���� ��" << endl; 
                cout << "<<"  <<  endl;
                return;
            }
            User *de = u;
            t->next = t->next->next;
            if(u -> next == NULL) tail = t;
            usernum --;
            delete de;  //�ͷ�ɾ���û��Ŀռ�
            delete_success = true;
        }
        t = u;
    } 
    if(delete_success == false) {
        cout << "<<    ��   δ��ѯ���û��� ��" << endl; 
        cout << "<<" << endl;
        return;
    }
    else {
        cout << "<<    ��   �ɹ�ɾ���û�  �"<< tmp_username << endl; 
        cout << "<<" << endl;
    }
}

User* UserDataController::find_user(const string username) const {
    User *p = head->next;
    while(p != NULL) {
        if(p -> username == username) return p;  //���ز�ѯ����
        p = p->next;
    }
    return NULL;  //����δ��ѯ��
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