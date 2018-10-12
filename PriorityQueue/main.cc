//c++ program
//design by >^.^<
//@date    2018-10-09 15:37:10
#include "PQ.h" 
#include <iostream>
#include <cstdio> 
#include <pthread.h> 

void test0()
{
    vector<int> ivec;
    ::srand(time(NULL)); 
    const int N = 10;
    for(int i = 0; i < N; ++i)
        ivec.push_back(rand() % 100);
    for(auto & a: ivec)
        printf("%4d", a);
    printf("\n");
    PriorityQueue<int> pqueue(ivec.begin(), ivec.end());
    for(int i = 0; i < N; ++i)
        printf("%4d", pqueue.delMax());
    printf("\n");
}

int main()
{
    test0();
    return 0;
}
