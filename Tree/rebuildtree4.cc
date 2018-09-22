//c++ program
//design by >^.^<
//@date    2018-09-17 21:40:00
//
#include <cstdio> 
#include <vector> 
#include <iostream> 
#include <unordered_map> 

using namespace std ;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
}; 

class Solution {
private:
    unordered_map<int, int> map;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode * root;
        for(size_t i = 0; i < inorder.size() ; ++i)
        {
            map[inorder[i]] = i;
        }
        helper(root, preorder, 0, preorder.size(), inorder, 0, inorder.size());
        return root;
    }
    using iter = vector<int>::iterator;

    void helper(TreeNode *& root , vector<int> preorder, int p1, int p2, vector<int> inorder, int i1, int i2)
    {
        if(p1 >= p2 || i1 >= i2)
           return ; 
        root = new TreeNode(preorder[p1]);
        auto ret = map[root->val]; 
        int len = ret - i1;
        ++p1;
        helper(root->left, preorder, p1, p1 + len, inorder,  i1, ret); 
        helper(root->right, preorder, p1 + len, p2, inorder,  ret + 1, i2); 
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
