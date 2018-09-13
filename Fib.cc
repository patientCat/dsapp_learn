//c++ program
//design by >^.^<
//@date    2018-09-13 09:21:18

#include <iostream> 

class Fib 
{ 
public: 
    // f= fib(k-1)  g= fib(k)
    Fib (int n = 0) {   while(g < n) next();    }
    int get()   {   return g;   }
    void next() {   g = f + g; f = g - f;   }
    void pre() {   int tmp = g; g = f; f = tmp - f;    }
     
private: 
    int f = 0;
    int g = 1;
}; 
