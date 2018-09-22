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

const int N = 8;
int chessboard[N][N];

// 整体思路
// 第行放置一个往后。
// 如果在皇后没有放完的情况下，无法放置。
// 则重新放置上一个皇后。

void placeQueen()
{
    vector<Queen> s;
    Queen q(0, 0);
    do{
        // 与已有棋局发生冲突，且仍可以改变位置
        while(count(s.begin(), s.end(), q) && q.y < N)
        {
            ++q.y;
        }
        // 找到位置
        if(q.y < N)
        {
            s.push_back(q);
            ++q.x;
            q.y = 0;
        }
        else
        {
            q = s[s.size() - 1];
            s.pop_back();
            ++q.y;
        }
    }while(s.size() < N);

    for(auto & a: s)
    {
        cout << a << endl;
    }
}


int main()
{
    placeQueen();
    return 0;
}
