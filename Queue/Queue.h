//c++ program
//design by >^.^<
//@date    2018-09-15 20:27:46
#include "List.h" 
#include <iostream> 

template <typename T>
class Queue 
: public List<T>
{ 
public: 
    void enqueue(const T & e) { List<T>::insertAsLast(e);    }
    T dequeue() { List<T>::remove(List<T>::first());    }
    T front()const {    return List<T>::first()->data;   }  
}; 

