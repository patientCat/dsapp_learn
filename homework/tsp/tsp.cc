//c++ program
//design by >^.^<
//@date    2018-09-23 11:21:18
#include <iostream> 
#include <cstdio> 

#define MAX 1001

int M[MAX][MAX];
int vertex[MAX]; // 记录是否被discovered
int stack1[MAX]; // dfs迭代版本需要的stack1

int top = -1;
int tStop = -1;
int size = 0;
struct Solution
{
    int n, m;
    void solve()
    {
        int x, y;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) // 完成图的构建
        {
            scanf("%d%d", &x, &y);
            M[x][y] = 1;
        }
        int max = 0;
        int ret;
        for(int i = 1; i <=n; ++i)
        {
            ret = tSort(i);
            if(ret > max)
                max = ret;
        }
        printf("%d", max);
    }
    
    int tSort(int s)
    {
        for(int i = 0; i < MAX; ++i)
        {
            vertex[i] = 0;
        }
        int cnt = 0;
        DFS(s, cnt);
        return cnt;
    }
    void DFS(int s, int &cnt) // 这里主要做的是顶点的位置和顶点本身的关系，我的做法是让其统一
    {
        vertex[s] = 1; // 1 == discovered ; 0 == undiscovered ; 2 == visited;
        for(int x = firstNbr(s); x > 0; x = nextNbr(s, x))
        {
            if(!vertex[x])
            {
                DFS(s, cnt);
            }
            else if(vertex[x] == 1){ // == discovered
                // 遇到环了
                return ;// 当前题的输入已经确定无环了
            }
            else {// == 2  : == visited
            }
        }
        stack1[++top] = s;
        ++size;
    }
    int firstNbr(int s)
    {
        return nextNbr(s, n + 1);
    }
    int nextNbr(int s, int v)
    {
        while(--v > 0 && !M[s][v])
            ;
        return v;
    }
};

int main()
{
    Solution().solve();
    return 0;
}
