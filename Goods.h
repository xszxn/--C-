#ifndef _GOOD_H_
#define _GOOD_H_
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
class Goods {
    private:
        int goodsid;  //货物编号
	    string goodsname;  //货物名称
        double price;  //货物价格
        int count;  //货物数量
    public:
        Goods *next;  //用于链表
        Goods() = default;
        ~Goods() = default;
        static void printtitle();
        int get_count();
        double get_price();
        friend class GoodsDataController;  //设置友元类，便于管理数据
        friend class OperationRecorder;  //设置友元类，便于管理数据
        friend ostream & operator << (ostream &, Goods &);
        friend bool operator - (Goods &, Goods &);  //重载-运算符，用于计算修改前后的区别
        friend bool cmp_by_id_up(Goods *, Goods *);   //cmp友元函数
        friend bool cmp_by_price_up(Goods *, Goods *); 
        friend bool cmp_by_count_up(Goods *, Goods *); 
        friend bool cmp_by_sumprice_up(Goods *, Goods *); 
        friend bool cmp_by_id_down(Goods *, Goods *); 
        friend bool cmp_by_price_down(Goods *, Goods *); 
        friend bool cmp_by_count_down(Goods *, Goods *); 
        friend bool cmp_by_sumprice_down(Goods *, Goods *); 
};

bool cmp_by_id_up(Goods *, Goods *);  //按照各元素的排序cmp函数
bool cmp_by_price_up(Goods *, Goods *);
bool cmp_by_count_up(Goods *, Goods *);
bool cmp_by_sumprice_up(Goods *, Goods *);
bool cmp_by_id_down(Goods *, Goods *);
bool cmp_by_price_down(Goods *, Goods *);
bool cmp_by_count_down(Goods *, Goods *);
bool cmp_by_sumprice_down(Goods *, Goods *);
#endif