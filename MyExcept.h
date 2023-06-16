#ifndef MYEXCEPT_H
#define MYEXCEPT_H
#include<string>
using namespace std;
class MyExcept {
    public:
        virtual string getWhat() = 0;
};
class MyInputError : public MyExcept {
    public:
        string getWhat() {
            return "<<   Input Error!";
        }
};
class MyMinusError : public MyExcept {
    public:
        string getWhat() {
            return "<<   Minus Error!";
        }
};
#endif