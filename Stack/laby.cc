//c++ program
//design by >^.^<
//@date    2018-09-18 22:11:53
// 迷宫算法
// 定义迷宫节点的各种状态

#include <iostream>
#include <stack> 
#include <cstdio> 

using std::stack; 
// 迷宫初始可用状态， 形成路径状态， 回朔状态， 墙
typedef enum{Available, Route, BaskTrack, Wall} Status;

// unknown 为未定方向，即在没有进行方向搜索之前的状态
typedef enum{Unkonwn, East, South, West, North, Noway} ESWN; // 定义的方向

// 返回下一个方向
inline ESWN nextESWN (ESWN eswn) { return ESWN(eswn + 1);}

struct Cell{
    int x, y;
    Status status;
    ESWN ingoing, outgoing; 
    Cell() = default;
    Cell(int xx, int yy, Status s = Available, ESWN i = Unkonwn, ESWN o = Unkonwn )
    : x(xx), y(yy), status(s), ingoing(i), outgoing(o) {}
    bool operator==(const Cell &rvalue)
    {
        if(x == rvalue.x && y == rvalue.y)
            return true;
        return false;
    }
};

#define Maxsize 24

Cell laby[Maxsize][Maxsize];

int randLaby(Cell *&startCell, Cell *&goalCell)
{
    srand(time(NULL));
    int ret;
    int size = Maxsize/2 + rand()%(Maxsize/2);
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++ j)
        {
            // 设置为墙
            laby[i][j] = Cell(i, j, Wall);
        }
    }
    for(int i = 1; i < size - 1; ++i)
    {
        for(int j = 1; j < size - 1; ++j)
        {
            ret = rand() % 4;
            if(ret)
            {
                // 3/4 设置为可用
                laby[i][j] = Cell(i,j, Available);
            }
        }
    }
    // 设置起始点 和 结束点
    startCell = &laby[rand() % (size - 2) + 1][rand() % (size - 2) + 1];
    startCell->status = Available;
    goalCell = &laby[rand() % (size - 2) + 1][rand() % (size - 2) + 1];
    goalCell->status = Available;
    return size;
}

inline Cell* neighbour(Cell *c)
{
    switch(c->outgoing)
    {
        case East :
            return &laby[c->x][c->y + 1];
        case South :
            return &laby[c->x + 1][c->y];
        case West :
            return &laby[c->x][c->y - 1];
        case North :
            return &laby[c->x - 1][c->y];
        default:
            exit(-1);
    }
    return nullptr;
}
inline Cell* advance(Cell *c)
{
    switch(c->outgoing)
    {
        case East:
            c = &laby[c->x][c->y+1];
            c->ingoing = East;
            break;
        case South:
            c = &laby[c->x+1][c-> y];
            c-> ingoing = South;
            break;
        case West:
            c = &laby[c->x][c->y-1];
            c-> ingoing = West;
            break;
        case North:
            c = &laby[c->x-1][c->y];
            c-> ingoing = North;
            break;
        default:
            exit(-1);
    }
    return c;
}

void display(int size, Cell start, Cell goal)
{
    system("clear");
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            switch(laby[i][j].status)
            {
                case Route : 
                    printf("*");
                    break;
                case Wall:
                    printf("#");
                    break;
                case BaskTrack:
                    printf("x");
                    break;
                case Available:
                    printf(" ");
                    break;
                default :
                    printf("-");
            }
            if(laby[i][j] == start)
               printf("\bS");
            else if(laby[i][j] == goal)
               printf("\bE");
        }
        printf("\n");
    }
}
bool findPath(Cell *start, Cell *goal, int size)
{
    if(start->status != Available || goal->status != Available)
    {
       return true;
    }
    stack<Cell*> s;
    start->status = Route;
    s.push(start);     
    do{
        // 展示迷宫
        display(size, *start, *goal);
        getchar();
        Cell *c = s.top();
        // 开始试探
        if(c == goal)
            return true;        
        // 试探所有方向
        while((c-> outgoing = nextESWN(c-> outgoing)) < Noway)
        {
            // 判断这个方向是否有路
            if(Available == neighbour(c)-> status) break;
        }
        // 如果所有方向都不行，就回朔
        if(c-> outgoing >= Noway && !s.empty())
        {
            c-> status = BaskTrack;
            c = s.top();
            s.pop();
        }
        else if( c->outgoing >= Noway && s.size() <= 1)
        {
            printf("failed\n");
            exit(-1);
        } 
        else{
            s.push( c = advance(c));
            c-> outgoing = Unkonwn;
            c-> status = Route;
        }
    }while(!s.empty());
    return false;
}

int main()
{
    Cell *start, *goal;
    int size = randLaby(start, goal);
    findPath(start, goal, size);
}
