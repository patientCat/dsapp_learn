//c++ program
//design by >^.^<
//@date    2018-09-17 08:30:54
#include <cstdio> 
#include <vector> 
#include <iostream> 

using std::vector; 

using namespace std;

struct Queen 
{ 
public: 
    Queen () = default;
    Queen (int xx, int yy)
    : x(xx)
    , y(yy) {}
     
    bool operator==(const Queen &rvalue)
    {
        if(x == rvalue.x || 
           y == rvalue.y ||
           x + y == rvalue.x + rvalue.y ||
           y - x == rvalue.y - rvalue.x)
            return true;
        return false;
    }

    int x;
    int y;
}; 
std::ostream & operator<<(std::ostream  &os, const Queen q)
{
    os << q.x << "," << q.y ;
    return os;
} 

const int N = 10;
int chessboard[N][N];

// 整体思路
// 1 如果皇后和已放置皇后序列不冲突，则加入皇后序列, 行号+1 goto 2, 否则改变当前皇后列的位置 goto 1
// 2 每行放置一个皇后
// 3 如果在皇后没有放完的情况下，无法放置。则重新改变上一个皇后的列 goto 1。

void placeQueen()
{
    vector<Queen> s;
    Queen q(0, 0);
    while(s.size() < N)
    {
        while(count(s.begin(), s.end(), q) && q.y < N)
        {
            ++q.y;
        }
        if( q.y < N)
        {
            s.push_back(q);
            ++q.x;
            q.y = 0;
        }
        else{
            if(!s.size())
            {
                cout << "no solution" << endl ;return ;
            }
            q = s[s.size() - 1];
            s.pop_back();
            ++q.y;
        }
    }
    for(auto &a : s)
    {
        cout << a << endl;
    }
}

int main()
{
    placeQueen();
    return 0;
}
