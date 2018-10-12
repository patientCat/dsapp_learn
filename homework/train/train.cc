//c++ program
//design by >^.^<
//@date    2018-09-23 08:53:24
#include <iostream>
#include <vector> 
#include <stack> 

using std::vector; 
using std::stack; 

struct Solution
{
    void train()
    {
        int n, m, t;
        vector<int> B;
        stack<int> A;
        stack<int> S;
        vector<int> record;
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
        {
            A.push(n-i);
            scanf("%d", &t);
            B.push_back(t);
        }
        int i;
        int flg = 0;
        for(i = 0; i < n; )
        {
            if(A.size() && S.empty())
            {
                S.push(A.top());
                A.pop();
                record.push_back(1);
            }
            else if(B[i] != S.top())
            {
                if(A.empty())
                {
                    flg = 1;
                    break;
                }
                S.push(A.top());
                A.pop();
                record.push_back(1);
            }
            else if(B[i] == S.top())
            {
                S.pop();
                record.push_back(0);
                ++i;
            }
        }
        if(flg)
            printf("no\n");
        else{
            for(int i = 0; (size_t)i < record.size(); ++i)
            {
                if(record[i])
                    printf("push\n");
                else
                    printf("pop\n");
            }
        }
    }
};

int main()
{
    Solution().train();
    return 0;
}
