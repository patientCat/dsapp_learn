//c++ program
//design by >^.^<
//@date    2018-10-13 19:17:29
#include "String.hpp" 
#include <cstdio> 
#include <iostream>

int testid = 0;
void test0()
{
    printf("test %d: KMP test \n", ++testid);
    String T = "abcabdabcabcd";
    String P = "abcabcd";
    int ret = String::KMP(T, P);
    printf("ret = %d\n", ret); 
}

int main()
{
    test0();
    return 0;
}


