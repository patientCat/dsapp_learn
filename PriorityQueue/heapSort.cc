//c++ program
//design by >^.^<
//@date    2018-10-09 16:36:27
#include <iostream>
#include <vector> 
#include <cstdio> 

#define ParentValid(i) (((i) -1) >> 1 > -1)
#define LChild(i) (((i) << 1 ) + 1)
#define RChild(i) (((i) + 1) << 1 )
using namespace std;

void percolateDown(vector<int> &ivec, int size, int i)
{
    int j = 0;
    while(LChild(i) < size) // 等价于LChildValid(i)
    {
        if(RChild(i) < size && ivec[RChild(i)] > ivec[LChild(i)])
            j = RChild(i);
        else
            j = LChild(i);
        if(ivec[i] >= ivec[j])
            break;
        std::swap(ivec[i], ivec[j]); 
        i = j;
    }
}

void makeHeap(vector<int> &ivec, int size)
{
    int lastInternal = (size >> 1) - 1;    
    for(int i = lastInternal; i > -1; --i)
        percolateDown(ivec, size, i);
}


void heapSort(vector<int> &ivec)
{
    int size = ivec.size();
    makeHeap(ivec, size);
    
    for(int i = size; i > 1; --i)
    {
        std::swap(ivec[0], ivec[i - 1]);
        //makeHeap(ivec, i - 1);
        percolateDown(ivec, i - 1, 0); 
    }    
}

void test0()
{
    vector<int>	ivec;
    ::srand(time(NULL));
    const int N = 15;
    for(int i = 0; i < N; ++i)
        ivec.push_back(rand() % 100);
    for(auto &a : ivec)
        printf("%3d", a);
    printf("\n"); 
    heapSort(ivec);
    for(auto &a : ivec)
        printf("%3d", a);
    printf("\n"); 
}

int main()
{
    test0();
    return 0;
}
