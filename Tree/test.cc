//c++ program
//design by >^.^<
//@date    2018-09-17 20:55:26
#include <cstdio> 
#include <iostream> 

struct ListNode{
    ListNode(int v, ListNode *s = nullptr) : data(v), succ(s) {};
    ListNode * insert(int v)
    {
        ListNode *n = new ListNode(v);
        return succ = n;
    }

    int data;
    ListNode * succ;
};

struct List{
    List() {  init(); }
    ListNode * insert(int e)
    {
        ListNode * n = new ListNode(e);
        if(!head)
            tail = head = n;
        else{
            tail->succ = n;
            tail = tail->succ;
        }  
        return n;
    }
    void init()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void display(){
        ListNode * tmp  = head;
        while(tmp)
        {
            printf("%3d", tmp->data);
            tmp = tmp->succ; 
        }
    }
    void reverse()
    {
        ListNode *pre = nullptr;
        ListNode *curr = nullptr;
        ListNode *next = head;
        while(next)
        {
            pre = curr;
            curr = next;
            next = next->succ;
            curr->succ = pre;  
        }
        curr = tail;
        tail = head;
        head = curr;  
    }
    ListNode * head;
    ListNode * tail;
    size_t size;
};

void test0()
{
    List l;
    for(int i = 0; i < 10; ++i)
    l.insert(i);
    l.display();
    printf("\n");
    l.reverse();
    l.display();
    printf("\n");
}
int main()
{
    ::srand(time(NULL));
    int arr[10];
    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 10;
    }
    test0();
    return 0;
}
