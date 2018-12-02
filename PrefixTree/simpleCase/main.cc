//c++ program
//design by >^.^<
//@date    2018-12-01 15:55:34
#include <iostream>
#include "prefixTree.hh" 

using namespace std;

int main()
{
    PrefixTree ptree{};
    ptree.insert("hello");
    ptree.insert("world");
    ptree.insert("butterfly");
    ptree.insert("jmx");

    cout << "prefixtree->search test" << endl;
    cout << "search -> hello : " << ptree.search("hello") << endl;
    cout << "search -> world : " << ptree.search("world") << endl;
    cout << "search -> lanlei : " << ptree.search("lanlei") << endl;

    cout << endl << endl;

    cout << "prefixtree->startsWith test" << endl;
    cout << "startsWith -> hel: " << ptree.startsWith("hello") << endl;
    cout << "startsWith -> wor: " << ptree.startsWith("world") << endl;
    cout << "startsWith -> lan: " << ptree.startsWith("lanlei") << endl;
    return 0;
}
