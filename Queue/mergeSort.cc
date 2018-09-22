//c++ program
//design by >^.^<
//@date    2018-09-19 19:31:13
#include <queue> 
#include <cstdio> 

// 使用队列的思想来实现归并排序
using std::queue; 

void merge(int *arr, int low, int mid, int high)
{
    queue<int> b;
    queue<int> c;
    queue<int> a;
    for(int i = low; i < mid; ++i)
    {
        b.push(arr[i]);
    }
    for(int i = mid; i < high; ++i)
    {
        c.push(arr[i]);
    }
    size_t len = high - low;
    while(a.size() != len)
    {
        if(b.size() && (c.empty() || b.front() <= c.front()))
        {
            a.push(b.front());
            b.pop();
        }
        if(c.size() && (b.empty() || c.front() < b.front()))
        {
            a.push(c.front());
            c.pop();
        }
    }
    for(int i = low; i < high; ++i)
    {
        arr[i] = a.front();
        a.pop();
    }
}

void mergeSort(int * arr, int low, int high)
{
    if(high - low < 2) 
        return ;
    int mid = (low + high) >> 1;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid, high);
    merge(arr, low, mid, high);
}


int main()
{
    const int maxI = 10;
    int arr[maxI] ;
    srand(time(NULL));
    for(int i = 0; i < maxI; ++i)
    {
        arr[i] = rand() % 100;
    }
    for(int i = 0; i < maxI; ++i)
    {
        printf("%3d", arr[i]);
    }
    printf("\n");
    mergeSort(arr, 0, maxI);
    for(int i = 0; i < maxI; ++i)
    {
        printf("%3d", arr[i]);
    }
    printf("\n");
    return 0;
}
