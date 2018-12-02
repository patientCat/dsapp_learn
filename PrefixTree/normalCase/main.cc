//c++ program
//design by >^.^<
//@date    2018-12-02 16:00:11
#include "Trie.hh" 
#include <iostream>
#include <cstdio> 

using namespace std;

void line()
{
    cout << "==============================" << endl;
}
void test()
{
    Trie<int> trieTree;
    trieTree.put("hello", 1);
    trieTree.put("world", 5);
    trieTree.put("problem", 10);
    trieTree.put("flower", 10);
    trieTree.put("floor", 2);
    trieTree.put("flyinthesky", 2);
    trieTree.put("float", 3);
    
    line();
    cout << "all keys :" << endl;
    queue<string> *q = trieTree.keys();
    while(q->size())
    {
        cout << q->front() << "  " ;
        q->pop();
    }
    cout << endl;

    line();
    cout << "keysWithPrefix \"fl\" " << endl;
    q = trieTree.keysWithPrefix("fl");
    while(q->size())
    {
        cout << q->front() << "  " ;
        q->pop();
    }
    cout << endl;

    line();
    cout << "keysThatMatch \"flo..\" " << endl;
    q = trieTree.keysThatMatch("flo..");
    while(q->size())
    {
        cout << q->front() << "  " ;
        q->pop();
    }
    cout << endl;
}
int main()
{
    test();
    return 0;
}
