#include <iostream>

using namespace std;

struct Listnode{
    int val;
    Listnode * next;
    Listnode(int val):val(val),next(nullptr){}
};

int main(){
    Listnode * node1 = new Listnode(1);
    Listnode * node2 = new Listnode(2);
    Listnode * node3 = new Listnode(3);
    Listnode * node4 = new Listnode(4);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = nullptr;
    Listnode * flag1 = node1;
    Listnode * flag2 = node2;
    Listnode * flag3 = nullptr;
    while(flag1 != nullptr){
        flag1->next = flag3;
        flag3 = flag1;
        flag1 = flag2;
        if(flag2 != nullptr)
        flag2 = flag2->next;
    }
    Listnode * flag = flag3;
    while(flag!= nullptr){
        cout << flag->val << " ";
        flag = flag->next;
    }
    return 0;
}