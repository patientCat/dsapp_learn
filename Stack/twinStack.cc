//c++ program
//design by >^.^<
//@date    2018-09-19 16:52:41
#include <iostream>
#include <vector> 

using std::vector; 

using namespace std;

class TwinStack 
{ 
public: 
    TwinStack () {
        _data.reserve(initialStackSize);
        _top1 = -1;
        _top2 = _data.capacity();
        _size = 0;
    }
    void push(char flg , int e);
    int size()const {   return _size;   }
    int top1()const {   if(_top1 > -1)return _data[_top1];  }
    int top2()const {   if((size_t)_top2 < _data.capacity()) return _data[_top2];   }

//private:
    void expand();
//private: 
    vector<int> _data;
    int _top1;
    int _top2;
    int _size;
    bool full()const;
    static int initialStackSize;
}; 

int TwinStack::initialStackSize = 5;

bool 
TwinStack::full()const
{
    if(_top1 + 1 == _top2)
        return true;
    return false;
}

void 
TwinStack::push(char flg , int e)
{
    expand();
    if(flg)
    {
        _data[++_top1] = e;
        ++_size;
    }
    else{
        _data[--_top2] = e;
        ++_size;
    }
}

void
TwinStack::expand()
{
    if(full())
    {
        int oldcapacity = _data.capacity();
        int capacity = 2 * oldcapacity;
        vector<int> save;
        for(int i = 0; i < oldcapacity; ++i)
            save.push_back(_data[i]);
        _data.reserve(capacity);
        for(int i = 0; i < capacity; ++i)
        {
            _data[i] = 0;
        }
        for(int i = 0; i < oldcapacity; ++i)
        {
            _data[i] = save[i];
        }
        int i, j;
        if(_top2 < oldcapacity)
        {
            for(i = capacity - 1, j = oldcapacity - 1; j >= _top2; --i, --j)
            {
                _data[i] = _data[j];
            }
            _top2 = ++i;
        }
        else{
             _top2 = capacity;
        }
    }
}

void test0()
{
    TwinStack ts;
    srand(time(NULL));
    for(int i = 0; i < 12; ++i)
    {
        ts.push(rand() % 2, i); 
    }
    cout << "栈中实际的数目size:" << ts.size() << endl;
    cout << "栈的容量capacity:" << ts._data.capacity() << endl;
    for(int i = 0; i < ts._data.capacity() ;  ++i)
    {
        cout << ts._data[i] << endl;
    }
    cout << ts.top1() << "  " << ts.top2() << endl;
}
int main()
{
    test0();
    return 0;
}

