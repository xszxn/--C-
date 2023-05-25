#ifndef _GOOD_H_
#define _GOOD_H_
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
class Goods {
    private:
        int goodsid;  //������
	    string goodsname;  //��������
        double price;  //����۸�
        int count;  //��������
    public:
        Goods *next;  //��������
        Goods() = default;
        ~Goods() = default;
        static void printtitle();
        int get_count();
        double get_price();
        friend class GoodsDataController;  //������Ԫ�࣬���ڹ�������
        friend class OperationRecorder;  //������Ԫ�࣬���ڹ�������
        friend ostream & operator << (ostream &, Goods &);
        friend bool operator - (Goods &, Goods &);  //����-����������ڼ����޸�ǰ�������
        friend bool cmp_by_id_up(Goods *, Goods *);   //cmp��Ԫ����
        friend bool cmp_by_price_up(Goods *, Goods *); 
        friend bool cmp_by_count_up(Goods *, Goods *); 
        friend bool cmp_by_sumprice_up(Goods *, Goods *); 
        friend bool cmp_by_id_down(Goods *, Goods *); 
        friend bool cmp_by_price_down(Goods *, Goods *); 
        friend bool cmp_by_count_down(Goods *, Goods *); 
        friend bool cmp_by_sumprice_down(Goods *, Goods *); 
};

bool cmp_by_id_up(Goods *, Goods *);  //���ո�Ԫ�ص�����cmp����
bool cmp_by_price_up(Goods *, Goods *);
bool cmp_by_count_up(Goods *, Goods *);
bool cmp_by_sumprice_up(Goods *, Goods *);
bool cmp_by_id_down(Goods *, Goods *);
bool cmp_by_price_down(Goods *, Goods *);
bool cmp_by_count_down(Goods *, Goods *);
bool cmp_by_sumprice_down(Goods *, Goods *);
#endif