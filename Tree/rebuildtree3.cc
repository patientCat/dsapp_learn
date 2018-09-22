//c++ program
//design by >^.^<
//@date    2018-09-17 21:40:00
//
#include <cstdio> 
#include <vector> 
#include <iostream> 

using namespace std ;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}; 

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode * root;
        helper(root, preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
        return root;
    }
    using iter = vector<int>::iterator;

    void helper(TreeNode *& root ,iter p1, iter p2, iter i1, iter i2)
    {
        if(p1 >= p2 || i1 >= i2)
           return ; 
        int rootval = *p1;
        root = new TreeNode(rootval);
        auto ret = find(i1, i2, rootval);
        int len = ret - i1;
        ++p1;
        helper(root->left, p1, p1 + len, i1, ret); 
        helper(root->right, p1 + len , p2, ret + 1, i2); 
        return;
    }
};

void preorder(TreeNode * root)
{
    using namespace std;
    if(!root)
        return ;
    cout << root->val << endl;  
    preorder(root->left);
    preorder(root->right);  
}
int main()
{
    vector<int> pre = {3, 9, 20, 15, 7};
    vector<int> in = {9, 3, 15, 20, 7}; 
    TreeNode * bintree = Solution().buildTree(pre, in);
    preorder(bintree);
}
