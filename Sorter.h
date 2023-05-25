#ifndef SORTER_H
#define SORTER_H

#include<iostream>
#include<vector>
#include<algorithm>
#include "Goods.h"

using namespace std;

class Sorter {
    public:
        Sorter(Goods*);
        ~Sorter() = default;

        void print();

        void sortBy(bool (*cmp)(Goods *, Goods *));

        void filter_price(const int);
        void filter_count(const int);
    private:
        vector<Goods*> arr;
};

#endif