//c++ program
//design by >^.^<
//@date    2018-09-17 11:47:12

#include "BinTree.h" 
#include <iostream>

using namespace std;
int TESTID;
struct Construct
{
    void operator()(BinNodePos(char) p)
    {
        char c;
        cin >> c;
        p->data = c; 
    }
};

struct Visit
{
    void operator()(int e)
    {
        std::cout << "   " << e << "  " ;
    }
};

void test0()
{
    BinTree<char> bt;
    bt.levelConstruct(Construct());    
}

// 先序遍历
void test1()
{
    using namespace std;
    cout << "testID:" << ++TESTID << " preorder traverse test " << endl;
    BinTree<int> bt;
    bt.constructFromTest();
    bt.preTraverseRecur(bt.root(), Visit());
    cout << endl;
    bt.preTraverseIter(bt.root(), Visit());
    cout << endl;
    bt.preTraverseIter2(bt.root(), Visit());
    cout << endl;
}

// 中序遍历
void test2()
{
    using namespace std;
    cout << "testID:" << ++TESTID << " inorder traverse test " << endl;
    BinTree<int> bt;
    bt.constructFromTest();
    bt.inTraverseRecur(bt.root(), Visit());
    cout << endl;
    bt.inTraverseIter(bt.root(), Visit());
    cout << endl;
}    

// 后序遍历
void test3()
{
    using namespace std;
    cout << "testID:" << ++TESTID << " postorder traverse test " << endl;
    BinTree<int> bt;
    bt.constructFromTest();
    bt.postTraverseRecur(bt.root(), Visit());
    cout << endl;
    bt.postTraverseIter(bt.root(), Visit());
    cout << endl;
}

// 层次遍历
void test4()
{
    using namespace std;
    cout << "testID:" << ++TESTID << " level traverse test " << endl;
    BinTree<int> bt;
    bt.constructFromTest();
    bt.levelTraverse(bt.root(), Visit());
    cout << endl;
}

// 逆层次遍历
void test5()
{
    using namespace std;
    cout << "testID:" << ++TESTID << " reverse level traverse test " << endl;
    BinTree<int> bt;
    bt.constructFromTest();
    bt.levelReverseTraverse(bt.root(), Visit());
    cout << endl;
}
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
