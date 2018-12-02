//c++ program
//design by >^.^<
//@date    2018-10-18 09:08:36
#include <iostream>
#include <cstdio> 
#include <vector> 

using Rank = int;
using namespace std;

class SearchMedthod 
{ 
public: 
    static Rank upper_bound(vector<int> &S, int e, Rank low, Rank high)
    {
        while(low < high)
        {
            int mid = low + ((high - low) >> 1);
            S[mid] <= e ? low = mid + 1 : high = mid;
        }
        return high;
    } 
    static Rank lower_bound(vector<int> &S, int e, Rank low, Rank high)
    {
        while(low < high)
        {
            int mid = low + ((high - low) >> 1);
            S[mid] < e ? low = mid + 1 : high = mid;
        }
        return low;
    }
private: 
}; 
int main()
{
    vector<int>	vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    for(size_t i = 0; i < vec.size(); ++i)
    {
        printf("%3d", vec[i]);
    }
    printf("\n");
    printf("%3d\n", SearchMedthod::upper_bound(vec, 3, 0, vec.size()));
    printf("%3d\n", SearchMedthod::upper_bound(vec, 4, 0, vec.size()));
    printf("%3d\n", SearchMedthod::upper_bound(vec, 100, 0, vec.size()));
    return 0;
}
