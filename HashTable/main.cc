//c++ program
//design by >^.^<
//@date    2018-11-24 19:18:06

#include "hashTable.hh" 

#include <iostream> 
#include <cstdio> 

using namespace std;

#define TEST(id, msg) \
    do{ \
        fprintf(stdout, "test_id = %d, %s\n", ++id, msg); \
    }while(0);

int ID;

void test()
{
    TEST(ID, "put test");
    Hashtable<int, int> hashtable{ 10 };
    hashtable.put(1, 1);
    hashtable.put(2, 2);
    hashtable.put(3, 3);
    hashtable.put(4, 4);

    cout << "---------------------" << endl;
    TEST(ID, "get test");
    cout << *hashtable.get(1) << endl;
    cout << *hashtable.get(2) << endl;

    TEST(ID, "remove test");
    hashtable.remove(1);
    hashtable.remove(2);
    hashtable.testprint();
}

int main()
{
    test();
    return 0;
}
