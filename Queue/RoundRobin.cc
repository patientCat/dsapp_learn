//c++ program
//design by >^.^<
//@date    2018-09-15 20:26:53
#include "Queue.cc" 
#include <iostream>

// 循环盘
void RoundRobin()
{
    Queue<int> que;
    while(!serve.close())
    {
        e = que.dequeue();
        serve(e);
        que.enqueue(e);
    }
}

int main()
{
    RoundRobin();
    return 0;
}
