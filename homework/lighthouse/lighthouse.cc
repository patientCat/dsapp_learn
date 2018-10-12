//c++ program
//design by >^.^<
//@date    2018-09-22 16:38:15
#include <cstdio> 
#include <cstdlib> 

#define MAX 300001

struct LightHouse
{
    LightHouse() = default;
    LightHouse(long xx, long yy)
    : x(xx), y(yy) {}
    long x;
    long y;
};

LightHouse arr[MAX];
char mark[MAX];

int compare(const void * a, const void * b)
{
    LightHouse lha = *(LightHouse *)a;
    LightHouse lhb = *(LightHouse *)b;
    return (lha.x > lhb.x);

}
struct Solution 
{ 
    void solve()
    {
        long n;
        cnt = 0;
        scanf("%ld", &n);
        long i = 0;
        for(; i < n; ++i)
        {
            scanf("%ld%ld", &arr[i].x, &arr[i].y);
        }
        qsort(arr, n, sizeof(LightHouse), compare);
        invInside(0, n);
        long long total = n * (n-1) >> 1;
        printf("%lld\n", total - cnt);
    }
    void invInside(long low, long high)
    {
        if(high - low < 2)
            return ;
        long mid = (low + high) >> 1;
        invInside(low, mid);
        invInside(mid, high);
        invBetween(low, mid, high);
    }
    void invBetween(long low, long mid, long high)
    {
        long j, k, i;
        long lenB = mid - low;
        long lenC = high - mid;
        LightHouse *A = arr + low;
        LightHouse *B = new LightHouse[lenB];
        LightHouse *C = arr + mid;
        for(long i = 0; i < lenB; ++i)
        {
            B[i] = A[i];
        }
        for(i = j = k = 0; j < lenB; )
        {
            if((lenC <= k || B[j].y <= C[k].y))
            {
                A[i++] = B[j++];
            }
            if(k < lenC && B[j].y > C[k].y)
            {
                A[i++] = C[k++];
                cnt += lenB - j;
            }
        }
        delete []B;
    }
    long long cnt = 0;
};  
int main()
{
    Solution().solve();
    return 0;
}
