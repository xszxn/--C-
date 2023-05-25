#include "Sorter.h"

Sorter::Sorter(Goods* p) {
    while(p->next != NULL) {
        arr.push_back(p->next);
        p = p->next;
    }
}

void Sorter::sortBy(bool (*cmp)(Goods *, Goods *)) {
    sort(arr.begin(), arr.end(), cmp);
}

void Sorter::print() {
    Goods::printtitle();
    for(int i = 0; i < arr.size(); i++) {
        cout << *arr[i];
    }
}

void Sorter::filter_count(const int k) {
    int a, b;
    if(k == 1) {
        cout << "<<" <<endl;
        cout <<  ">>    �����:"; 
        cin >> a;
        sortBy(cmp_by_count_up);
        int cnt = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i]->get_count() <= a)
                cnt ++;
            else break;
        }
        cout << "<<\n";
        cout <<  "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        Goods::printtitle();
        for(int i = 0; i < cnt; i ++) {
            cout << *arr[i];
        }
    }
    else if(k == 2) {
        cout << "<<" <<endl;
        cout << ">>    �����:"; 
        cin >> a;
        sortBy(cmp_by_count_down);
        int cnt = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i]->get_count() >= a)
                cnt ++;
            else break;
        }
        cout << "<<\n";
        cout <<  "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        Goods::printtitle();
        for(int i = 0; i < cnt; i ++) {
            cout << *arr[i];
        }
    }
    else {
        cout << "<<" <<endl;
        cout << ">>    ����ڵ���:"; 
        cin >> a;
        cout << ">>    ��С�ڵ���:"; 
        cin >> b;
        sortBy(cmp_by_count_up);
        int cnt = 0;
        int position = -1;
        for(int i = 0; i < arr.size(); i++) {
            int tt = arr[i]->get_count();
            if(tt >= a && tt <= b) {
                if(position == -1) position = i;
                cnt ++;
            }
            if(tt > b) break;
        }
        cout << "<<\n";
        cout << "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        if(cnt != 0) {
            for(int i = position; i < position + cnt; i ++) {
            cout << *arr[i];
        }
        }
    }
}

void Sorter::filter_price(const int k) {
    int a, b;
    if(k == 1) {
        cout << "<<" <<endl;
        cout << ">>    �����:"; 
        cin >> a;
        sortBy(cmp_by_price_up);
        int cnt = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i]->get_price() <= a)
                cnt ++;
            else break;
        }
        cout << "<<\n";
        cout <<  "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        if(cnt > 0) {
            Goods::printtitle();
            for(int i = 0; i < cnt; i ++) {
                cout << *arr[i];
            }
        }
    }
    else if(k == 2) {
        cout << "<<" <<endl;
        cout << ">>    �����:"; 
        cin >> a;
        sortBy(cmp_by_price_down);
        int cnt = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(arr[i]->get_price() >= a)
                cnt ++;
            else break;
        }
        cout << "<<\n";
        cout << "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        if(cnt > 0) {
            Goods::printtitle();
            for(int i = 0; i < cnt; i ++) {
                cout << *arr[i];
            }
        }
    }
    else {
        cout << endl;
        cout << ">>    ����ڵ���:"; 
        cin >> a;
        cout << ">>    ��С�ڵ���:"; 
        cin >> b;
        sortBy(cmp_by_price_up);
        int cnt = 0;
        int position = -1;
        for(int i = 0; i < arr.size(); i++) {
            int tt = arr[i]->get_price();
            if(tt >= a && tt <= b) {
                if(position == -1) position = i;
                cnt ++;
            }
            if(tt > b) break;
        }
        cout << "<<\n";
        cout << "<<    �ﹲ��ѯ�� " << cnt << " �������" << endl;
        if(cnt > 0) {
            Goods::printtitle();
            for(int i = position; i < position + cnt; i ++) {
                cout << *arr[i];
            }
        }
    }
}