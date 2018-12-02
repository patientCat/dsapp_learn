//c++ program
//design by >^.^<
//@date    2018-10-12 18:58:31

#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <cstring> 
#include <cassert> 
#include <cstdio> 

using Rank = int;
class String 
{ 
public: 
    String (const char *S, int i, int k)
    {
        _size = k - i;
        _string = new char[_size + 1]();
        for(int j = i; j < k; ++j)
            _string[j] = S[j];
    }
    String (const char *S); 
    ~String (); 
     
    size_t length() const   {   return _size;   }
    char& operator[](Rank i) const    {   assert(i < _size); return _string[i];  }
    String substr(Rank i, int k)
    {
        return {_string, i, i + (int)k};
    }
    String prefix(int k) {   return {_string, 0, k}; }
    String suffix(int k) {   return {_string, (int)_size - k, (int)_size}; }
    String& concat(String &T)
    {
        char *temp = new char[_size + T._size + 1]();
        memcpy(temp, _string, _size);
        delete []_string;
        memcpy(temp + _size, T._string, T._size);
        return *this;
    }
static Rank KMP(const String &T, const String &P);
static int* buildNext(const String &P); 

private: 
    char * _string;
    size_t _size;
friend bool operator==(const String &lvalue, const String &rvalue);
}; 

bool operator==(const String &lvalue, const String &rvalue)
{
    for(int i = 0; i < (int)lvalue.length(); ++i)
    {
        if(lvalue[i] != rvalue[i])
            return false;
    }
    return true;
}


String::String(const char *S)
{
    int m = strlen(S);
    _size = m;
    _string = new char[m + 1]();
    memcpy(_string, S, m);
} 

String::~String()
{
    if(_string)
        delete []_string;
} 


int * 
String::buildNext(const String &P)
{
    int m = P.length(), j = 0;
    int *Next = new int[m]();
    int t = Next[0] = -1;
    while(j < m - 1)
    {
        if(0 > t || P[j] == P[t])
        {
            ++j;
            ++t;
            Next[j] = (P[j] != P[t] ? t : Next[t]);
        }
        else{
            t = Next[t];
        }
    }
    return Next;
}

Rank
String::KMP(const String &T, const String &P)
{
    int n = T.length(), i = 0;
    int m = P.length(), j = 0;
    int *Next = buildNext(P);
    while(j < m && i < n)
    {
    //printf("i = %d , j = %d\n", i, j);
    //printf("T[i] = %c , P[j] = %c\n", T[i], P[j]);
    //getchar();
        if(0 > j || T[i] == P[j])
        {
            ++i; ++j;
        }
        else{
            j = Next[j];
        }
    }
    delete Next;
    printf("i = %d , j = %d\n", i, j);
    return i - j;
}
#endif /* String_hpp */

