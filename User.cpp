#include "User.h"

string User::get_password() {
    return password;
}

void User::change_password() {
    cout << "<<    ��  �������µ�����  �";
    cin >> password;
    return; 
}

string User::getname() {
    return username;
}

string User::get_usertype() {
    return usertype;
}

int User::getid() {
    return userid;
}

void User::printtitle() {
    cout << endl;
    cout << "<<    " << std::left << setw(15) << "�û����" << std::left << setw(15) << "�û�����" << std::left << setw(15) << "�û�����" << endl;
}

ostream & operator << (ostream &os, User &p) {
    os << "<<    " << std::left << setw(15) << p.userid << std::left << setw(15) << p.username << std::left << setw(15) << p.usertype <<endl;
    return os;
}


