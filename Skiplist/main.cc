//c++ program
//design by >^.^<
//@date    2018-11-22 22:09:32
#include "Skiplist.hh" 
#include <iostream>
#include <cstdio> 

#define TEST(id, msg) \
    do{ \
       fprintf(stdout, "test_id = %d, %s\n", ++id, msg); \
    }while(0);

int ID;
void test()
{
    TEST(ID, "insert test");
    Skiplist<int, int> slist;
    ::srand(time(NULL)); 
    for(int i = 0; i < 30; ++i)
    {
        auto ret = i;
        slist.put(ret, ret);
    }
    slist.print();
    
    cout << "------------------------" << endl;

    TEST(ID, "remove test");
    slist.remove(0);
    slist.remove(1);
    slist.remove(2);
    slist.print();

    cout << "------------------------" << endl;

    TEST(ID, "get test");
    cout << *slist.get(3) << endl;
    cout << *slist.get(5) << endl;
    cout << *slist.get(9) << endl;
}

int main()
{
    test();
    return 0;
}
