//c++ program
//design by >^.^<
//@date    2018-09-17 21:40:00
//
#include <cstdio> 
#include <vector> 

using namespace std ;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() = default;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}; 

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode * root;
        rebuildtreehelper(&root, preorder.begin(), preorder.end() -1, inorder.begin(), inorder.end() -1);
        return root;
    }
    using iter = vector<int>::iterator;

    void rebuildtreehelper(TreeNode ** root ,iter p1, iter p2, iter i1, iter i2)
    {
        if(p1 > p2 || i1 > i2)
           return ; 
        int rootval = *p1;
        *root = new TreeNode(rootval);
        auto ret = find(i1, i2, rootval);
        iter iterL = ret - 1;
        iter iterR = ret + 1;
        int lenL = iterL - i1;
        int lenR = i2 - iterR;

        if(lenL >= 0)
        rebuildtreehelper(&root->left, p1 + 1, p1 + 1 + lenL, i1, iterL); 
        if(lenR >= 0)
        rebuildtreehelper(&root->right, p2 - lenR, p2, iterR, i2); 
        return;
    }
};
