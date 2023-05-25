#include "Goods.h"

void Goods::printtitle() {
    cout << "<<" << endl;
    cout << "<<    " << std::left << setw(15) << "货物编号" << std::left << setw(15) << "货物名称" << std::left << setw(15) << "货物单价" << std::left << setw(15) << "货物数量" << std::left << setw(15) << "货物总价" << endl;
}

double Goods::get_price() {
    return price;
}

int Goods::get_count() {
    return count;
}

ostream & operator << (ostream &os, Goods &p) {
    os << "<<    " << std::left << setw(15) << p.goodsid << std::left << setw(15) << p.goodsname << std::left << setw(15) << p.price << std::left << setw(15) << p.count << std::left << setw(15) << p.price * p.count << endl;
    return os;
}

bool operator - (Goods &a, Goods &b) {
    if(a.price != b.price) {
        cout << "<<            |-修改单价  单价:" << a.price << "--->"<< std::left << setw(10) << b.price << endl;
        return true;
    }
    else if(a.count < b.count) {
        cout << "<<            |-货物入库  数量:" << a.count << "--->"<< std::left << setw(10) << b.count << endl;
        return true;
    }
    else if(a.count > b.count) {
        cout << "<<            |-货物出库  数量:" << a.count << "--->"<< std::left << setw(10) << b.count << endl;
        return true;
    }
    return false;
}

bool cmp_by_id_up(Goods *a, Goods  *b) {
    return a->goodsid < b->goodsid;
}

bool cmp_by_price_up(Goods *a, Goods  *b) {
    return a->price < b->price;
}

bool cmp_by_count_up(Goods *a, Goods  *b) {
    return a->count < b->count;
}

bool cmp_by_sumprice_up(Goods *a, Goods  *b) {
    return a->price * a->count < b->price * a->count;
}

bool cmp_by_id_down(Goods *a, Goods  *b) {
    return a->goodsid > b->goodsid;
}

bool cmp_by_price_down(Goods *a, Goods  *b) {
    return a->price > b->price;
}

bool cmp_by_count_down(Goods *a, Goods  *b) {
    return a->count > b->count;
}

bool cmp_by_sumprice_down(Goods *a, Goods  *b) {
    return a->price * a->count > b->price * a->count;
}

