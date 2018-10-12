//c++ program
//design by >^.^<
//@date    2018-09-23 10:11:50

#include <cstdio> 

#define MAX 4000001
int pre[MAX];
int post[MAX];
int in[MAX];
int postmap[MAX];
int premap[MAX];

struct TreeNode{
    TreeNode(int dd) : data(dd), left(nullptr), right(nullptr) {}
    int data;
    TreeNode * left;
    TreeNode * right;
};

struct Solution{
    TreeNode * solve()
    {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &pre[i]);
        }
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &post[i]);
        }
        for(int i = 0; i < n; ++i)
        {
            premap[pre[i]] = i;
        }
        for(int i = 0; i < n; ++i)
        {
            postmap[post[i]] = i;
        }
        return rebuild(0, n - 1, 0, n - 1);
    }

    TreeNode * rebuild(int l1, int h1, int l2, int h2)
    {
        if(l1 > h1 || l2 > h2)
            return nullptr;
        TreeNode * root = new TreeNode(pre[l1]);
        int l = l1 + 1;
        int r = h2 - 1;
        if(l <= h1)
        root->left = rebuild(l, premap[post[h2-1]] - 1, l2, postmap[pre[l]]);
        if(l2 <= r)
        root->right = rebuild(premap[post[r]], h1, postmap[pre[l]] + 1, r);
        return root;
    }
};

TreeNode * stack[MAX];
int top = -1;
int size = 0;
void inOrder(TreeNode * bt)
{
    while(1)
    {
        while(bt)
        {
            stack[++top] = bt;
            ++size;
            bt = bt->left;
        }
        if(!size)
            break;
        bt = stack[top--];
        --size;
        printf("%d ", bt->data);
        //printf("%d", bt->data);
        bt = bt ->right;
    }
}

int main()
{
    TreeNode * result = Solution().solve();
    inOrder(result);
    return 0;
}
