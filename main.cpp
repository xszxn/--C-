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
void Log_in() {  //程序开始时的登入界面
    system("cls");
    UserDataController usercontroller;
	cout << "<<    ☆仓库管理系统☆"  << endl;
	cout << "<<                @by_朱鑫楠"  << endl;
	cout << "<<" << endl;
	cout << "<<      1.员  工登入  "  << endl;
	cout << "<<      2.管理员登入  "  << endl;
    cout << "<<      0.退  出      "  << endl;
	cout << "<<" << endl;
    cout << ">>    等待输入：" ;
	char x;
	cin >> x;
	switch(x) {
	case '0':
        exit(0);
        break;
	case '1':
        cout << "<<\n<<\n>>    请输入用户名：";
		cin >> name;
        now_user = usercontroller.find_user(name);
		if(now_user != NULL){  //判断是否存在用户
            if(now_user -> get_usertype() == "admin") {
                cout << "<<\n<<\n<<    当前用户为管理员用户，请切换登入模式！";
                system("pause");
                break;
            }
            cout << ">>    请输入密码：";
		    cin >> password;
            int trytimes = 5;
            bool log = true;
            while(!usercontroller.login_success(now_user, password)){
                trytimes --;
                if(trytimes > 0) {
                    cout << "<<\n<<    密码错误,还剩下" << trytimes << "次机会";
                    cout << "<<\n<<\n>>    请输入密码：";
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
        cout << "<<\n<<\n>>    请输入管理员名：";
		cin >> name;
        now_user = usercontroller.find_user(name);
		if(now_user != NULL){  //判断是否存在用户
            if(now_user -> get_usertype() == "user") {
                cout << "<<\n<<\n>>    当前用户为管理员用户，请切换登入模式！" << "\n\n\n";
                system("pause");
                break;
            }
            cout << ">>    请输入密码：";
		    cin >> password;
            int trytimes = 5;
            bool log = true;
            while(!usercontroller.login_success(now_user, password)){
                trytimes --;
                if(trytimes > 0) {
                    cout << "<<\n<<    密码错误,还剩下" << trytimes << "次机会";
                    cout << "<<\n<<\n>>    请输入密码：";
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
        cout << "<<\n<<\n<<    选择异常，请重新选择！" << "<<\n";
                system("pause");
        break;
	}
}

void Menu(bool is_admin, UserDataController &usercontroller) {
    GoodsDataController goodscontroller;
    OperationRecorder recorder;
    while(1) {
        system("cls");
        cout << "<<    ★"<< now_user->getname() <<", 欢迎进入仓库管理系统★ " << endl;
        cout << "<<" << endl;
        cout << "<<          1.添加货物信息      " << endl;
        cout << "<<          2.修改货物信息      " << endl;
        cout << "<<          3.删除货物信息      " << endl;
        cout << "<<          4.查询货物信息      " << endl;
        cout << "<<          5.显示所有货物信息  " << endl;
        cout << "<<          6.修改用户密码      " << endl;
        if(is_admin) {
            cout << "<<          7.显示所有用户信息  " << endl;
            cout << "<<          8.创建新的用户      " << endl;
            cout << "<<          9.删除用户信息      " << endl;
        }
        cout << "<<          f.查询货物信息修改记录      " << endl;
        cout << "<<          0.退出登陆          " << endl;
        cout << "<<" << endl;
        try{
            cout << ">>    等待输入：" ;
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