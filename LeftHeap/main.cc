//c++ program
//design by >^.^<
//@date    2018-10-12 18:13:37
#include "LeftHeap.h" 

#include <iostream>
#include <cstdio> 

int testid;
struct Visit
{
    void operator()(int &e)
    {
        printf("%3d", e);
    }
};
void test0()
{
    printf("test %d: 左式堆简单测试\n", ++testid);
    int arr[10];
    ::srand(time(NULL)); 
    const int N = 10;
    printf("%3d 个随机数的值\n", N);
    for(int i = 0; i < N; ++i)
    {
        arr[i] = static_cast<double>(rand()) / RAND_MAX * 99;
        printf("%3d", arr[i]);
    }
    printf("\n");
    PQ_LeftHeap<int> left_heap(arr, 10);
    printf("左式堆层次遍历\n");
    left_heap.levelTraverse(left_heap._root, Visit());
    printf("\n");
    printf("左式堆删除顶点\n");
    left_heap.delMax();
    left_heap.levelTraverse(left_heap._root, Visit());
    printf("\n");
    printf("左式堆插入顶点\n");
    int n = 1000;
    left_heap.insert(n);
    left_heap.levelTraverse(left_heap._root, Visit());
    printf("\n");
}

int main()
{
    test0();
    return 0;
}
