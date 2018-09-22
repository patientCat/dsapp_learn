//c++ program
//design by >^.^<
//@date    2018-09-15 10:14:01
#include <iostream>
#include <vector> 
#include <stack> 

using std::vector; 
using std::stack; 
//栈混洗

//简单例子， 3, 1, 2 不是 1，2，3的栈混洗

using namespace std;

void initStackA(stack<int> &a, int n)
{
    cout << "input seq " << endl;
    int c;
    for(int i = 0; i < n; ++i)
    {
        cin >> c;
        a.push(c);
    }
}
bool stackPermutation(vector<int> &b, int n)
{
    stack<int> a; 
    stack<int> c;
    initStackA(a, n);

    int i = 0;
    while(i != n)
    {
        // 算法过程如下
        // c不空的情况下，从c取，如果是，c.pop且b游标++, 
        //                      如果不是的情况下从a取，
        // c 为空的情况下从a取

        if( !c.empty() && b[i] == c.top())
        {
            c.pop(); ++i;
        }
        else{
            bool get = false;
            while(!a.empty())
            {
                if(b[i] == a.top())
                {
                    ++i; a.pop(); get = true; break;
                }
                else{
                    c.push(a.top()); a.pop();
                }
            }
            if(!get)
                return false;
        }
    }
    return true;
}

int func(vector<int> &v, int n)
{
    cout << "output seq" << endl;
    int num;
    for(int i = 0; i < n; ++i)
    {
        cin >> num;
        v.push_back(num);
    }
    return 1;
}

int main()
{
    vector<int> input;
    int n;
    while(cout << "size of stack" << endl, cin >> n, func(input, n))
    {
        if(stackPermutation(input, n))
        {
            cout << "yes  " << endl;
        }
        else{
            cout << "not  " << endl;
        }
        cout << endl;
        input.clear();
        input.shrink_to_fit();
    }
}
