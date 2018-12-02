//c++ program
//design by >^.^<
//@date    2018-10-16 09:45:34

#include "Sort.hpp" 

#include <cstdio> 
#include <iostream>
#include <vector> 

using namespace std;

void test0()
{
    srand(time(NULL)); 
    const int N = 15;
    int arr[N];
    for(int i = 0; i < N; ++i)
    {
        arr[i] = rand() % 100;
        printf("%3d", arr[i]);
    }
    printf("\n");
    Sort::quickSort(arr, 0, N); 
    for(int i = 0; i < N; ++i)
        printf("%3d", arr[i]);
    printf("\n");
}

void test1()
{
    const int N = 10;
    int arr[N] = {0, 1, 3, 3, 5, 3, 6, 3, 3, 3};
    for(int i = 0; i < N; ++i)
    {
        printf("%3d", arr[i]);
    }
    printf("\n");
    int maj = 0;
    auto ret = Sort::majority(arr, 0, N, maj);
    if(ret)
        printf("the majority is %3d\n", maj);
    else 
        printf("no majority\n");
}

int main()
{
    printf("test : majority\n");
    test1();
    return 0;
}

