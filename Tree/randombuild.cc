//c++ program
//design by >^.^<
//@date    2018-09-17 21:40:00
//
#include <cstdio> 
#include <vector> 
#include <iostream> 
#include <queue> 

// 通过随机的方式建树
using namespace std ;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
}; 

class Build {
public:
    void randomBuild(TreeNode * &root, int n)
    {
        int ret = rand() % n;
        if(!ret)
            return ;
        root = new TreeNode(rand() % n + 1);
        randomBuild(root->left, n - 1); 
        randomBuild(root->right, n - 1); 
    }

    TreeNode * buildFromArr(int * arr, int size)
    {
        int ff = 0;
        queue<TreeNode *> q;
        TreeNode * root = new TreeNode(arr[ff]);
        q.push(root);
        while(ff < size - 1)
        {
            TreeNode * tnode = q.front();
            q.pop();
            if(arr[++ff] != -1)
            {
                tnode->left  = new TreeNode(arr[ff]);
                q.push(tnode->left); 
            }
            if(arr[++ff] != -1)
            {
                tnode->right  = new TreeNode(arr[ff]);
                q.push(tnode->right); 
            }
        }
        return root;
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

void test0()
{
    srand(time(NULL));
    Build build;
    TreeNode *tree1 = nullptr;
    build.randomBuild(tree1, 10);
    preorder(tree1);
}

void test1()
{
    int tree[] = {1,2,5,3,4,-1,6,-1,-1,-1,-1,-1,-1};
    //int tree[] = {1, 2, 3, -1, -1, -1, -1};
    int size = 7;
    Build b;
    TreeNode *root = b.buildFromArr(tree, size);
    preorder(root);
}

int main()
{
    test1();
    return 0;
}
