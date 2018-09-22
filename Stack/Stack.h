//c++ program
//design by >^.^<
//@date    2018-09-16 09:26:37
#include "List.h" 

template <typename T>
class Stack 
: public List<T>
{ 
public: 
    Stack () = default; 
    ~Stack () = default; 
    T top()const {  return List<T>::last()->data;   }   
    void push(const T &e) { List<T>::insertAsLast(e);   }
    T pop() { return List<T>::remove(List<T>::last());  }  
     
}; 


