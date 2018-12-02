//c++ program
//design by >^.^<
//@date    2018-10-16 09:45:34
#ifndef _SORT_HPP_
#define _SORT_HPP_
#include <vector> 
#include <cstdio>

using namespace std;

class Sort 
{ 
public: 
static void quickSort(int *S, int low, int high)
{
    if(high - low < 2)
        return ;
    int pivot = partition(S, low, high - 1);
    quickSort(S, low, pivot);
    quickSort(S, pivot + 1, high);
}

static int partition(int *S, int low, int high)
{
    std::swap(S[low], S[low + rand() %(high - low + 1)]);
    int candidate = S[low];
    while(low < high)
    {
        while((low < high) && candidate <= S[high])
            --high;
        S[low] = S[high];
        while((low < high) && S[low] <= candidate)
            ++low;
        S[high] = S[low];
    } 
    S[low] = candidate;
    return low;
}

static bool majority(int *S, int low, int high, int &maj)
{
    maj = majElectRecur(S, low, high);
    printf("maj = %3d\n", maj);
    return majCheck(S, low, high, maj);
}

static bool majCheck(int *S, int low, int high, int &maj)
{
    int counter = 0;
    int size = high - low;
    for(int i = low; i < high; ++i)
    {
        if(maj == S[i])
            ++counter;
    }
    return 2 *counter > size;
}

static int majElectCandidate(int *S, int low, int high)
{
    int maj;
    for(int c = 0, i = low; i < high; ++i)
    {
        if(c == 0)
        {
            maj = S[i];
            c = 1;
        }
        else{
            maj == S[i] ? ++c : --c;
        }
    }
    return maj;
}

static int majElectRecur(int *S, int low, int high)
{
    int maj = S[low];
    for(int c = 1, i = low + 1; i < high; ++i)
    {
        if(2 * c == (i - low))
            maj = majElectRecur(S, i, high);
        else{
            if(maj == S[i])
                ++c;
        }
    }
    return maj;
}
private: 
}; 

#endif /* Sort_hpp */
