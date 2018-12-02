//c++ program
//design by >^.^<
//@date    2018-10-17 18:50:16
#include <iostream>
#include <vector> 

using namespace std;

using Rank = int;
class SortMedthod 
{ 
public: 
    // 九大排序
    // 冒泡 选择 插入
    static void bubbleSort(vector<int> &S, Rank low, Rank high)
    {
        while(low + 1 < high)
            bubble(S, low, high--);
    }
    static void selectSort(vector<int> &S, Rank low, Rank high)
    {
        while(low + 1 < high)
        {
            int maxpos = selectMax(S, low, high--);
            std::swap(S[maxpos], S[high]);
        }
    }
    // 为了实现就地插入排序
    // 还是需要一个二分查找
    static void insertSort(vector<int> &S, Rank low, Rank high)
    {
        for(int i = low + 1; i < high; ++i)
        {
            int k = binarySearch(S, S[i], low, i);
            int dup = S[i];
            for(int j = i; j > k; --j)
            {
                S[j] = S[j - 1];
            }
            S[k] = dup;
        }
    }
    // 归并 堆排 快排
    // 堆排序
    static void heapSort(vector<int> &S, Rank low, Rank high)
    {
        int size = high - low;
        makeHeap(S, size);
        for(; size > 1; --size)
        {
            std::swap(S[low], S[low + size - 1]); 
            percolateDown(S, low, size - 1);
        }
    }

    // 归并排序
    static void mergeSort(vector<int> &S, Rank low, Rank high)
    {
        if(high - low < 2)
            return ;
        Rank mid = (low + high) >> 1;
        mergeSort(S, low, mid);
        mergeSort(S, mid, high);
        merge(S, low, mid, high);
    }
    // 快速排序 -- 核心思路 -- 确认轴点
    static void quickSort(vector<int> &S, Rank low, Rank high)
    {
        if(high - low < 2)
            return ;
        Rank pivot = partition(S, low, high - 1);
        quickSort(S, low, pivot);
        quickSort(S, pivot + 1, high); 
    }
    // 桶排 计数 基数 
    // 希尔排序（忽略）
    static Rank binarySearch(vector<int> &S, int target, Rank low, Rank high)
    {
        while(low < high)
        {
            int mid = (low + high) >> 1;
            S[mid] < target ? low = mid + 1: high = mid;
        }
        return low;
    }
    static Rank selectMax(vector<int> &S, Rank low, Rank high) 
    {
        int mmax = S[low];
        int pos = low;
        for(int i = low + 1; i < high; ++i)
           if(S[i] > mmax)
           {
               mmax = S[i]; 
               pos = i;
           }
        return pos;
    }
    static void bubble(vector<int> &S, Rank low, Rank high)
    {
        for(int i = low + 1; i < high; ++i)
        {
            if(S[i - 1] > S[i])
                std::swap(S[i - 1], S[i]); 
        }
    }
    static void makeHeap(vector<int> &S, Rank size)
    {
        int lastP = size / 2 - 1;
        for(int i = lastP; i > -1 ; --i)
        {
            percolateDown(S, i, size);
        }
    }

    static void percolateDown(vector<int> &S, Rank pos, Rank size)
    {
        // lchild(i) = 2 * i + 1;
        while(2 * pos + 1 < size) // HasLchild(i) 
        {
            int lchild = 2 * pos + 1;
            int rchild = lchild + 1;
            int bigchild = lchild;
            if(rchild < size && S[rchild] > S[lchild])
                ++bigchild;
            if(S[pos] >= S[bigchild])
                break;
            std::swap(S[pos], S[bigchild]); 
            pos = bigchild;
        }
    }
    static void merge(vector<int> &S, Rank low, Rank mid, Rank high)
    {
        int lenA = high - low;
        int lenB = mid - low;
        int lenC = lenA - lenB;
        vector<int>::iterator A = S.begin() + low; 
        vector<int> B;
        for(int i = 0; i < mid; ++i)
            B.push_back(A[i]);
        vector<int>::iterator C = S.begin() + mid; 
        for(int i = 0, j = 0, k = 0; j < lenB;)
        {
            if( k >= lenC || B[j] <= C[k])
                A[i++] = B[j++];
            if( k < lenC && C[k] < B[j])
                A[i++] = C[k++];
        }
    }

    static Rank partition(vector<int> &S, Rank low, Rank high)
    {
        std::swap(S[low], S[low + rand() % (high - low + 1)]);
        Rank candidate = S[low];
        while(low < high)
        {
            while(low < high && S[high] >= candidate)
                --high ;
            S[low] = S[high];
            while(low < high && S[low] <= candidate)
                ++low;
            S[high] = S[low];
        }
        S[low] = candidate;
        return low;
    }
};  

void test0(vector<int> vec)
{
    printf("快速排序:\n");
    SortMedthod::quickSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}
void test1(vector<int> vec)
{
    printf("归并排序:\n");
    SortMedthod::mergeSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}

void test2(vector<int> vec)
{
    printf("堆排序:\n");
    SortMedthod::heapSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}

void test3(vector<int> vec)
{
    printf("冒泡排序:\n");
    SortMedthod::bubbleSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}

void test4(vector<int> vec)
{
    printf("选择排序:\n");
    SortMedthod::selectSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}
void test5(vector<int> vec)
{
    printf("插入排序:\n");
    SortMedthod::insertSort(vec, 0, vec.size()); 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
}

int main()
{
    vector<int>	vec; 
    const int N = 15;
    ::srand(time(NULL)); 
    printf("初始N = %d 随机序列\n", N);
    for(int i = 0; i < N; ++i)
    {
        vec.push_back(rand() % 100);
        printf("%3d", vec[i]);
    }
    printf("\n");

    test0(vec);
    test1(vec);
    test2(vec);
    test3(vec);
    test4(vec);
    test5(vec);

    return 0;
}
