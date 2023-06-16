#include "UserDataController.h"
#include "GoodsDataController.h"
#include "OperationRecorder.h"
#include "MyExcept.h"
string name;
string password;
User *now_user;
void Log_in();
void Menu(bool, UserDataController &);
int main() {
    while(1) {
        Log_in();
    }
    return 0;
}
void Log_in() {  //����ʼʱ�ĵ������
    system("cls");
    UserDataController usercontroller;
	cout << "<<    ��ֿ����ϵͳ��"  << endl;
	cout << "<<                @by_�����"  << endl;
	cout << "<<" << endl;
	cout << "<<      1.Ա  ������  "  << endl;
	cout << "<<      2.����Ա����  "  << endl;
    cout << "<<      0.��  ��      "  << endl;
	cout << "<<" << endl;
    cout << ">>    �ȴ����룺" ;
	char x;
	cin >> x;
	switch(x) {
	case '0':
        exit(0);
        break;
	case '1':
        cout << "<<\n<<\n>>    �������û�����";
		cin >> name;
        now_user = usercontroller.find_user(name);
		if(now_user != NULL){  //�ж��Ƿ�����û�
            if(now_user -> get_usertype() == "admin") {
                cout << "<<\n<<\n<<    ��ǰ�û�Ϊ����Ա�û������л�����ģʽ��";
                system("pause");
                break;
            }
            cout << ">>    ���������룺";
		    cin >> password;
            int trytimes = 5;
            bool log = true;
            while(!usercontroller.login_success(now_user, password)){
                trytimes --;
                if(trytimes > 0) {
                    cout << "<<\n<<    �������,��ʣ��" << trytimes << "�λ���";
                    cout << "<<\n<<\n>>    ���������룺";
		            cin >> password;
                }
                else {
                    log = false;
                    break;
                }
            }
            if(log)
			    Menu(false, usercontroller);
        }
		break;	
	case '2':
        cout << "<<\n<<\n>>    ���������Ա����";
		cin >> name;
        now_user = usercontroller.find_user(name);
		if(now_user != NULL){  //�ж��Ƿ�����û�
            if(now_user -> get_usertype() == "user") {
                cout << "<<\n<<\n>>    ��ǰ�û�Ϊ����Ա�û������л�����ģʽ��" << "\n\n\n";
                system("pause");
                break;
            }
            cout << ">>    ���������룺";
		    cin >> password;
            int trytimes = 5;
            bool log = true;
            while(!usercontroller.login_success(now_user, password)){
                trytimes --;
                if(trytimes > 0) {
                    cout << "<<\n<<    �������,��ʣ��" << trytimes << "�λ���";
                    cout << "<<\n<<\n>>    ���������룺";
		            cin >> password;
                }
                else {
                    log = false;
                    break;
                }
            }
            if(log)
			    Menu(true, usercontroller);
        }
		break;	
    default:
        cout << "<<\n<<\n<<    ѡ���쳣��������ѡ��" << "<<\n";
                system("pause");
        break;
	}
}

void Menu(bool is_admin, UserDataController &usercontroller) {
    GoodsDataController goodscontroller;
    OperationRecorder recorder;
    while(1) {
        system("cls");
        cout << "<<    ��"<< now_user->getname() <<", ��ӭ����ֿ����ϵͳ�� " << endl;
        cout << "<<" << endl;
        cout << "<<          1.��ӻ�����Ϣ      " << endl;
        cout << "<<          2.�޸Ļ�����Ϣ      " << endl;
        cout << "<<          3.ɾ��������Ϣ      " << endl;
        cout << "<<          4.��ѯ������Ϣ      " << endl;
        cout << "<<          5.��ʾ���л�����Ϣ  " << endl;
        cout << "<<          6.�޸��û�����      " << endl;
        if(is_admin) {
            cout << "<<          7.��ʾ�����û���Ϣ  " << endl;
            cout << "<<          8.�����µ��û�      " << endl;
            cout << "<<          9.ɾ���û���Ϣ      " << endl;
        }
        cout << "<<          f.��ѯ������Ϣ�޸ļ�¼      " << endl;
        cout << "<<          0.�˳���½          " << endl;
        cout << "<<" << endl;
        try{
            cout << ">>    �ȴ����룺" ;
            char t;
            cin >> t;
            system("cls");
            switch(t) { 
                case '1': 
                    goodscontroller.add_info(recorder, now_user->getname());
                    break;
                case '2':
                    goodscontroller.modify_goodsinfo(recorder, now_user->getname());
                    break;
                case '3':
                    goodscontroller.delete_info(recorder, now_user->getname());
                    break;
                case '4':
                    goodscontroller.query_goodsinfo();
                    break;
                case '5':
                    goodscontroller.show_list();
                    break;
                case '6':
                    now_user->change_password();
                    break;
                case '7':
                    if(is_admin)
                        usercontroller.show_list();
                    break;
                case '8':
                    if(is_admin)
                        usercontroller.add_info();
                    break;
                case '9':
                    if(is_admin)
                        usercontroller.delete_info();
                    break;
                case 'f':
                        recorder.show_list();
                    break;
                case 'F':
                        recorder.show_list();
                    break;
                case '0':
                    return;
                default:
                    throw MyInputError();
            }
        }
        catch(MyExcept &e) {
            cout << e.getWhat() << "\n";
        }
        cout << "<<\n" << endl;
        system("pause");
	}
}