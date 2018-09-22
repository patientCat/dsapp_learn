//c++ program
//design by >^.^<
//@date    2018-09-19 11:30:07

#include <cstdio> 
#include <stack> 
#include <utility> 

using std::stack; 
using std::pair; 

const int Maxsize = 24;
char laby[Maxsize][Maxsize];

using Point = pair<int, int>;
class Laby 
{ 
public:
public: 
    Laby () {   init();     }
    void init()
    {
        srand(time(NULL));
        size = Maxsize / 2 + rand() % (Maxsize / 2);
        start.first = rand() % (size - 2) + 1;
        start.second = rand() % (size - 2) + 1;
        goal.first = rand() % (size - 2) + 1;
        goal.second = rand() % (size - 2) + 1;
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                laby[i][j] = '#';
            }
        }
        for(int i = 1; i < size - 1; ++i)
        {
            for(int j = 1; j < size - 1; ++j)
            {
                if(rand() %4)
                    laby[i][j] = ' ';
            }
        }
        laby[start.first][start.second] = ' ';
        laby[goal.first][goal.second] = ' ';
    }

    void display()
    {
        system("clear");
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                if(i == goal.first && j == goal.second)
                    printf("G");
                else
                    printf("%c", laby[i][j]);
            }
            printf("\n");
        }
    }

    Point findAvailableDirection(Point p){
        for(int i = 0; i < 4; ++i)
        {
            if(laby[p.first + 1][p.second] == ' ')
                return std::make_pair(p.first + 1, p.second);
            if(laby[p.first - 1][p.second] == ' ')
                return std::make_pair(p.first - 1, p.second);
            if(laby[p.first][p.second + 1] == ' ')
                return std::make_pair(p.first , p.second + 1);
            if(laby[p.first][p.second - 1] == ' ')
                return std::make_pair(p.first , p.second - 1);
        }
        return std::make_pair(-1, -1);
    }

    bool findPath()
    {
        stack<Point> path;
        path.push(start);
        laby[start.first][start.second] = '*';
        do{
            display();
            getchar();
            Point tmp = path.top();
            if(tmp == goal)
                return true;
            // 首先要找当前点中一个可以的方向, 如果四个方向都不行就返回!
            auto ret = findAvailableDirection(tmp);
            if(ret == Point(-1,-1))
            {
                // 需要回朔
                laby[tmp.first][tmp.second] = '!';
                path.pop();
            }
            else{
                laby[tmp.first][tmp.second] = '*';
                path.push(ret);
            }
        }while(!path.empty());
        return false;
    }
     
private: 
    Point start;
    Point goal;
    int size;
}; 

bool operator==(Point a, Point b)
{
    if(a.first == b.first && a.second == b.second)
        return true;
    return false;
}

int main()
{
    Laby l;
    l.findPath();
    return 0;
}
