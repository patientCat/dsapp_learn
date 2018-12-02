//c++ program
//design by >^.^< //@date    2018-10-16 15:11:13
#include <cstdio> 
#include <iostream>
#include <vector> 

using namespace std;

class GetMedian 
{ 
public: 
    static int trivalMedian(vector<int> &S1, int low1, int n1, vector<int> &S2, int low2, int n2)
    {
        int high1 = low1 + n1, high2 = low2 + n2;
        vector<int> S; // 俩个有序子向量归并为一个有序向量
        while((int)S.size() < n1 + n2)
        {
            while((low1 < high1) && (low2 >= high2 || S1[low1] <= S2[low2]))
                S.push_back(S1[low1++]);
            while((low2 < high2) && (low1 >= high1 || S2[low2] < S1[low1]))
                S.push_back(S2[low2++]);
        }
        cout << "merged sequence: \n" << endl;
//        for(size_t i = 0; i < S.size() ; ++i)
//            printf("%3d", S[i]);
//        printf("\n");
        return S[(n1 + n2) / 2];
    }

    static int median(vector<int> &S1, int low1, vector<int> &S2, int low2, int n)
    {
        if(n < 3)
            return trivalMedian(S1, low1, n, S2, low2, n);
        int mid1 = low1 + n / 2, mid2 = low2 + n / 2;
        if(S1[mid1] < S2[mid2])
            return median(S1, mid1, S2, low2, n + low1 - mid1);
        else if(S1[mid1] > S2[mid2])
            return median(S1, low1, S2, mid2, n + low2 - mid2);
        else
            return S1[mid1];
    }

    static int median(vector<int> &A, vector<int> &B)
    {
        if(!A.size() || !B.size())
            return -1;
        if(A.size() < B.size())
            return median(B, A); // 保证A始终是较为大的那个序列
        int imin = 0, imax = A.size(), half_len = (A.size() + B.size() + 1) / 2;
        int max_of_left = 0;
        int min_of_right = 0;
        while(imin <= imax)
        {
            size_t i = (imin + imax) >> 1;
            size_t j = half_len - i;
            if(i < A.size() && B[j - 1] > A[i]) // i太小，需要增大
                imin = i + 1;
            else if(i > 0 && A[i - 1] > B[j]) // i太大， 需要减小
                imax = i - 1;
            else{
                // i is perfect
                if(i == 0)
                    max_of_left = B[j - 1];
                else if(j == 0)
                    max_of_left = A[i - 1];
                else 
                    max_of_left = std::max(A[i - 1], B[j - 1]);
                if(i == A.size())
                    min_of_right = B[j];
                else if(j == B.size())
                    min_of_right = A[j];
                else
                    min_of_right = std::min(A[i], B[j]); 
                break;
            }
        }
        return min_of_right;
    }

    static int quickSelect(vector<int> &S, int k)
    {
        --k;
        for(int low = 0, high = S.size() - 1; low < high;)
        {
            int i = low, j = high;
            int pivot = S[low];
            while(i < j)
            {
                while(i < j && S[j] >= pivot)
                    --j;
                S[i] = S[j];
                while(i < j && S[i] <= pivot)
                    ++i;
                S[j] = S[i];
            }
            S[i] = pivot; 
            if(i == k)
                return S[i];
            else if( i > k)
                high = i - 1;
            else
                low = i + 1;
        }
        return -1;
    }
    static void quickSortIter(vector<int> &A, int low, int high, int K)
    {
        for(int i, j; low < high; )
        {
            i = low;
            j = high - 1;
            int candidate = A[low]; // 也可以先做一次随机置换
            while(i < j)
            {
                while(i < j && A[j] >= candidate)
                    j--;
                A[i] = A[j];
                while(i < j && A[i] <= candidate)
                    ++i;
                A[j] = A[i];
            }
            A[i] = candidate;
            if(i < K)
                high = i;
            if(i >= K)
                low = i + 1;
        }
    }
private: 
}; 

int main()
{
    vector<int> S1 = {1, 3, 7, 8, 9};
    vector<int> S2 = {2, 4, 5, 8, 10};
    vector<int> S3 = {2, 4, 5, 8, 10, 11};
    vector<int> S4 = {10, 4, 3, 8, 1, 11};
    cout << "test 蛮力算法:" << endl;
    cout << GetMedian::trivalMedian(S1, 0, S1.size(), S2, 0, S2.size()) << endl;
    cout << "test 减而治之:" << endl;
    cout << GetMedian::median(S1, 0, S2, 0, S1.size()) << endl; 
    cout << "test 任意俩个有序向量求中位数:" << endl;
    cout << GetMedian::median(S1, S2) << endl;
    cout << "test quickSort:" << endl;
//    cout << GetMedian::quickSelect(S4, 3) << endl; 
    GetMedian::quickSortIter(S4, 0, S4.size(), 3);
    cout << S4[3] << endl;
    return 0;
}
