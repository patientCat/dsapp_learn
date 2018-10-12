//c++ program
//design by >^.^<
//@date    2018-09-22 15:25:34
#include <iostream>
#include <cstdio> 
#include <cstring> 

// 思路
// 简单分析了下，需要大量的插入和删除操作
// 第一种情况，插入一个珠子，原序列不发生任何变化
const int maxI = 10001;
struct solution 
{ 
public: 
    void zuma()
    {
        // 输入input
        char input[maxI] = {0};
        int n, num;
        char a;
        scanf("%s", input);
        scanf("%d", &n);
        int len = strlen(input);
        int l, r, i;
        while(n--)
        {
  //          printf("input\n");
            scanf("%d %c", &num, &a);
            for(i = len; i > num; --i)
            {
                input[i] = input[i-1];
            }
            input[i] = a;
            ++len;
            while(1)
            {
            for(l = num; l > 0; --l)
            {
                if((l-1)>-1 && input[l-1] != input[num])
                    break;
            }
 //           printf("l = %d\n",l);
            for(r = num; r < len; ++r)
            {
                if(input[r] != input[num])
                    break;
            }
//            printf("r = %d\n",r);
            if(r - l > 2)
            {
                int save = l;
                for(int i = r; i < len; ++i)
                {
                    input[l++] = input[i];
                }
                len = l;
                num = save;
            }
            else{
                break;
            }
            }
        if(len > 0)
        for(int i = 0; i < len; ++i)
            printf("%c", input[i]);
        else
            printf("-");
        printf("\n");
        } 
    } 
}; 
int main()
{
    solution s;
    s.zuma();
    return 0;
}
