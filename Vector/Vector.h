//c++ program
//design by >^.^<
//@date    2018-09-12 17:27:20

#include "Fib.h" 
#include <initializer_list> 
#include <algorithm> 
#include <functional> 

using std::initializer_list; 
using std::function; 
using Rank = int;

template <typename T>
class Vector 
{ 
public:  /*构造与析构*/
    Vector (int capacity = DefaultCapacity); 
    Vector (T *A, Rank low, Rank high){   copyFrom(A, low, high); } 
    Vector (T *A, int n){ copyFrom(A, 0, n);  } 
    Vector (const Vector<T> &rhs){  copyFrom(rhs._elem, 0, rhs._size);  } 
    Vector (const Vector<T> &&rhs);
    Vector (initializer_list<T> s);
    ~Vector () = default;

public:  /*接口*/
    // 通用接口
    Rank size()const    {   return _size;   }
    // 增
    Rank insert(Rank pos, const T &e);
    Rank push_back(const T &e)  {   return insert(_size, e);    }
    // 删
    Rank remove(Rank low, Rank high);
    Rank remove(Rank pos)   {   remove(pos, pos + 1); }
    // 查
    Rank find(const T &e, Rank low, Rank high)const;
    // 改
    T & operator[](Rank r)  {   return _elem[r];    }
    // 遍历
    // 以模板的方式
    template <typename VST>
    void Traverse(int low, int high, VST visit);
    // 以注册函数的方式
    void Traverse2(int low, int high, function<void(T)> visit);
    // 去重
    int deduplicate();

    // 有序接口
    void sort(int low, int high)
    {
        srand(time(NULL));
        int choose = rand() % 3;
        switch(choose)
        {
            case 1:
                bubbleSort(low, high);
                break;
            case 2:
                selectSort(low, high);
                break;
            case 3:
                mergeSort(low, high);
                break;
        }
    }
    // 查找 
    int search(int value, int low, int high)
    {
        srand(time(NULL));
        int choose = rand() % 2;
        switch(choose)
        {
            case 1:
                return binSearch(value, low, high);
            case 2:
                return fibSearch(value, low, high);
            case 3:
                return insertSearch(value, low, high);
        }
    }
    // 去重
    int uniquify();

protected: /*内部函数*/
    void copyFrom(T *arr, int low, int high);
    void expand();
    int bubble(int low, int high);
    void bubbleSort(int low, int high);
    Rank max(int low, int high);
    void selectSort(int low, int high);
    void mergeSort(int low, int high);
    void merge(int low, int mid, int high);
    
    int fibSearch(int value, int low, int high);
    int binSearch(int value, int low, int high);
    int insertSearch(int value, int low, int high);

private: /*成员*/ 
    Rank    _size;
    int     _capacity;
    T*      _elem;
    static int DefaultCapacity;
}; 

template <typename T> int Vector<T>::DefaultCapacity = 3;  

template <typename T> 
void 
Vector<T>::copyFrom(T *arr, int low, int high)
{
    _elem = new T[2 * (high - low)];
    _size = 0;
    while(low< high)
    {
        _elem[_size++] = arr[low++];
    }
}

template <typename T>
Vector<T>::Vector(int capacity)
: _size(0)
, _capacity(capacity)
, _elem(new T[capacity])
{}

template <typename T>
Vector<T>::Vector(const Vector<T> &&rhs)
{
    _elem = rhs._elem;
    _size = rhs._size;
    _capacity = rhs._capacity;
}

template <typename T>
Vector<T>::Vector(initializer_list<T> s)
{
    for(auto & a : s)
    {
        push_back(a);
    }
}

template <typename T>
Rank 
Vector<T>::insert(Rank pos, const T &e)
{
    expand();
    for(int i = _size; i > pos; --i)
    {
        _elem[i] = _elem[i-1];
    }
    _elem[pos] = e;
    ++_size;
    return pos;
}

template <typename T>
void 
Vector<T>::expand()
{
    if(_size < _capacity)
       return ;
    _capacity = (_capacity > DefaultCapacity) ? _capacity : DefaultCapacity;
    _capacity <<= 1;
    T * oldelem = _elem;
    _elem = new T[_capacity];
    for(int idx = 0 ; idx < _size; ++idx)
    {
        _elem[idx] = oldelem[idx];
    }
    delete []oldelem;
}

template <typename T>
Rank 
Vector<T>::remove(Rank low, Rank high)
{
    if(high == low) return 0;
    Rank oldsize = _size;
    while(high < _size)
    {
        _elem[low++] = _elem[high++];
    }
    _size = low;
    return oldsize - _size;
}

template <typename T>
Rank 
Vector<T>::find(const T &e, Rank low, Rank high)const
{
    if(low == high) return low-1;
    while(low < high--)
    {
        if(_elem[high] == e)
            break ;
    }
    return high;
}


template <typename T>
template <typename VST>
void 
Vector<T>::Traverse(int low, int high, VST visit)
{
    for(Rank i = low; i < high; ++i)
    {
        visit(_elem[i]);
    }
}

template <typename T>
void 
Vector<T>::Traverse2(int low, int high, function<void (T)> visit)
{
    for(Rank i = low; i < high; ++i)
    {
        visit(_elem[i]);
    }
}

template <typename T>
int 
Vector<T>::deduplicate()
{
    int oldsize = _size;
    for(int i = 0; i < _size;)
    {
        if(find(_elem[i], 0, i) > 0)
            remove(i);
        else
            ++i;
    } 
    return oldsize - _size;
}

template <typename T>
int 
Vector<T>::bubble(int low, int high)
{
    int last = low;
    while(++low < high)
    {
        if(_elem[low-1] > _elem[low])
        {
            last = low;
            std::swap(_elem[low-1], _elem[low]);
        } 
    }
    return last;
} 

template <typename T>
void 
Vector<T>::bubbleSort(int low, int high)
{
    while(low + 1 < (high = bubble(low, high--)));
}

template <typename T>
int 
Vector<T>::fibSearch(int value, int low, int high)
{
    Fib fib(high - low);
    while(low < high)
    {
        while( high - low < fib.get()) fib.pre();
        int mid = low + fib.get() - 1;
        if(value < _elem[mid])
            high = mid;
        else if( _elem[mid] < value)
            low = mid + 1;
        else 
            return mid;
    }
    return -1; 
}

template <typename T>
int 
Vector<T>::binSearch(int value, int low, int high)
{
    while(low < high)
    {
        int mid = (high + low ) >> 1;
        value < _elem[mid] ? high = mid : low = mid + 1;
    }
    return --low;
}

template <typename T>
int
Vector<T>::insertSearch(int value, int low, int high)
{
    while(low < high)
    {
        int mid = low + (high - low) * (value - _elem[low]) / (_elem[high] - _elem[low]);
        value < _elem[mid] ? high = mid : low = mid + 1;
    }
    return --low;
}

template <typename T>
Rank 
Vector<T>::max(int low, int high)
{
    Rank mx = high;
    while(low < high--)
    {
        if(_elem[high] > _elem[mx])
            mx = high;
    }
    return high;
}

template <typename T>
void 
Vector<T>::selectSort(int low, int high)
{
    while(low < --high)
    {
        swap(_elem[max(low, high)], _elem[high]);
    }
}

template <typename T>
void 
Vector<T>::mergeSort(int low, int high)
{
    if(high - low <= 1)
        return ;
    int mid = (low + high) >> 1;
    mergeSort(_elem, low, mid);
    mergeSort(_elem, mid, high);
    if(_elem[mid - 1] > _elem[mid])
        merge(_elem, low, mid, high);
}

template <typename T>
void 
Vector<T>::merge(int low, int mid, int high)
{
    int lenB = mid - low;
    int lenC = high - mid;
    int *A = _elem + low;
    int *B = new int(lenB);
    int *C = _elem + mid;
    for(int i = 0; i<lenB; ++i)
        B[i] = A[i];
    for(int i = 0, j = 0, k = 0; j < lenB; )
    {
        if(B[j] <= C[k] || lenC <= k)
            A[i++] = B[j++];
        if(k < lenC && C[k] < B[j])
            A[i++] = C[k++];
    }
    delete B;
}

template <typename T>
int 
Vector<T>::uniquify()
{
    int oldsize = _size;
    int i = 0, j = 0;
    while(++j < _size)
    {
        if(_elem[j] != _elem[i])
            _elem[++i] = _elem[j];
    }
    _size = i + 1;
    return oldsize - _size;
}
