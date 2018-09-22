//c++ program
//design by >^.^<
//@date    2018-09-17 11:11:09
#include <iostream>
#include <string> 
#include <vector> 

using std::string; 
using std::vector; 

struct BinNode{
    BinNode(int d)
    : data(d) , left(nullptr) , right(nullptr) {}
    int data;
    BinNode * left;
    BinNode * right;
};

using iter = vector<int>::iterator;

BinNode * rebuildtreehelper(iter p1, iter p2, iter i1, iter i2);

BinNode* rebuildtree(vector<int> pre, vector<int> in)
{
    if(!pre.empty() || in.empty())
        return nullptr;
    return rebuildtreehelper(pre.begin(), pre.end()  - 1, in.begin(), in.end() - 1);
}

BinNode * rebuildtreehelper(iter p1, iter p2, iter i1, iter i2)
{
    if(p1 > p2 || i1 > i2)
       return nullptr; 
    int rootval = *p1;
    BinNode * root = new BinNode(rootval);
    auto ret = find(i1, i2, rootval);
    iter iterL = ret - 1;
    iter iterR = ret + 1;
    int lenL = iterL - i1;
    int lenR = i2 - iterR;

    if(lenL >= 0)
        root->left =  rebuildtreehelper(p1 + 1, p1 + 1 + lenL, i1, iterL); 
    if(lenR >= 0)
        root->right =  rebuildtreehelper( p2 - lenR, p2, iterR, i2); 
    return root;
}

void preorder(BinNode * root)
{
    using namespace std;
    if(!root)
        return ;
    cout << root->data << endl;  
    preorder(root->left);
    preorder(root->right);  
}
int main()
{
    vector<int> pre = {3, 9, 20, 15, 7};
    vector<int> in = {9, 3, 15, 20, 7}; 
    BinNode * bintree = rebuildtree(pre, in);
    preorder(bintree);
}
