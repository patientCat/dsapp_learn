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
    TreeNode* buildTree(vector<int>& postorder, vector<int>& inorder) {
        TreeNode * root;
        for(size_t i = 0; i < inorder.size() ; ++i)
        {
            map[inorder[i]] = i;
        }
        helper(root, postorder, 0, postorder.size(), inorder, 0, inorder.size());
        return root;
    }
    using iter = vector<int>::iterator;

    void helper(TreeNode *& root , vector<int> postorder, int p1, int p2, vector<int> inorder, int i1, int i2)
    {
        if(p1 >= p2 || i1 >= i2)
           return ; 
        root = new TreeNode(postorder[p2 - 1]);
        auto ret = map[root->val]; 
        int len = ret - i1;
        helper(root->left, postorder, p1, p1 + len, inorder,  i1, ret); 
        helper(root->right, postorder, p1 + len, p2 - 1, inorder,  ret + 1, i2); 
        return;
    }
};

void postorder(TreeNode * root)
{
    using namespace std;
    if(!root)
        return ;
    cout << root->val << endl;  
    postorder(root->left);
    postorder(root->right);  
}
int main()
{
    vector<int> post = {9, 15, 7, 20, 3};
    vector<int> in = {9, 3, 15, 20, 7}; 
    TreeNode * bintree = Solution().buildTree(post, in);
    postorder(bintree);
}
