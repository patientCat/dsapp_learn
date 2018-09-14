#include "LinkNode.h" 

#include <cassert> 
#include <functional> 

using std::function; 

template <typename T>
class List 
{ 
public: 
    List () {   init(); } 
    List (int n); // 用作排序测试，在列表中随机生成n个值
    List (Pos(T) p , int n) { init(); copyNodes(p, n);  }
    List (const List &l)   {   init(); copyNodes(l.first(), l.size()); }
    List (T *arr, int low, int high)    {   init(); copyNodes(arr, low, high);  }
    ~List ()    {   while(_size) remove(_header->succ); delete _header; delete _trailer; }  

public:
    // general interface
    int size() const {   return _size;   }
    Pos(T) first() const    {   if(_size) return _header->succ; return nullptr; } 
    Pos(T) last() const     {   if(_size) return _trailer->pred; return nullptr;    } 
    Pos(T) insertAsFirst(const T &e);
    Pos(T) insertAsLast(const T &e);
    Pos(T) insertBefore(Pos(T) p, const T &e);
    Pos(T) insertAfter(Pos(T) p, const T &e);
    Pos(T) find(const T &e, int n, Pos(T) p);
    Pos(T) find(const T &e);
    T remove(Pos(T) p);
    int deduplicate();
    template <typename VST>
    void traverse(VST visit);
    void traverse2(function<void (T)> visit);
     
    // sorted interface
    Pos(T) search(const T &e, int n, Pos(T) p) const;
    Pos(T) search(const T &e) const;
    int uniquify();
    void sort(Pos(T) low, int n){
        ::srand(time(NULL)); int choose = rand() % 4;
        switch(choose){
            case 0:
                bubbleSort(low, n);
                break;
            case 1:
                insertSort(low, n);
                break;
            case 2:
                selectSort(low, n);
                break;
            case 3:
                mergeSort(low, n);
                break;
        }
    }

    void reverse();
    void reverse2();
    void reverse3();
    void reverse4();
    // test
    void bubbleSort(Pos(T) p, int n);
    void insertSort(Pos(T) p, int n);
    void selectSort(Pos(T) p, int n);
    void mergeSort(Pos(T) p, int n);
protected:
    void init();
    void copyNodes(Pos(T) p, int n);
    void copyNodes(T *arr, int low, int high);

    Pos(T) bubble(Pos(T) low, Pos(T) high);
    Pos(T) selectMax(Pos(T) low, Pos(T) high);
    void merge(Pos(T) A, int mid, int n);

private: 
    int             _size;
    Pos(T)          _header;
    Pos(T)          _trailer;
}; 

template <typename T>
List<T>::List (int n)
{
    init();
    ::srand(time(NULL)); 
    for(int i = 0; i < n; ++i)
    {
        insertAsLast(rand() % 100);
    }
}

template <typename T>
Pos(T) 
List<T>::insertAsFirst(const T &e)
{
    return insertAfter(_header, e);
}

template <typename T>
Pos(T) 
List<T>::insertAsLast(const T &e)
{
    return insertBefore(_trailer, e);
}

template <typename T>
Pos(T) 
List<T>::insertBefore(Pos(T) p, const T &e)
{
    ++_size;
    return p->insertAsPred(e); 
}

template <typename T>
Pos(T) 
List<T>::insertAfter(Pos(T) p, const T &e)
{
    ++_size;
    return p->insertAsSucc(e); 
}

template <typename T>
void 
List<T>::init()
{
    _size = 0;
    _header = new LinkNode<T>();
    _trailer = new LinkNode<T>();
    _header->pred = nullptr; _header->succ = _trailer;
    _trailer->pred = _header; _trailer->succ = nullptr;
}

template <typename T>
Pos(T) 
List<T>::find(const T &e, int n, Pos(T) p)
{
    while(n--)
    { 
        if(e == (p = p->pred)->data)
           return p; 
    }
    return nullptr;
}

template <typename T>
Pos(T) 
List<T>::find(const T &e)
{
    find(e, _size, _trailer);
}

template <typename T>
void 
List<T>::copyNodes(Pos(T) p, int n)
{
    while(n--)
    {
        insertAsLast(p->data);
        p = p->succ;  
    }
}
    
template <typename T>
void 
List<T>::copyNodes(T *arr, int low, int high)
{
    while(low < high)
    {
        insertAsLast(arr[low++]);
    }
}

template <typename T>
T
List<T>::remove(Pos(T) p)
{
    T save = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;    
    --_size;
    return save;
}

template <typename T>
int 
List<T>::deduplicate()
{
    int oldsize = _size;
    Pos(T) scan = _header, q;
    int r = 0;
    while((scan = scan->succ)  != _trailer)
    {
        if((q = find(scan->data, r, scan)))
        {
            remove(q);   
        }
        else{
            ++r;
        }
    } 
    return oldsize - _size;
}

template <typename T> template <typename VST>
void 
List<T>::traverse(VST visit)
{
    Pos(T) scan = _header;
    if(_size)
    {
        while((scan = scan->succ) != _trailer)
        {
            visit(scan->data); 
        } 
    }
}

template <typename T>
void 
List<T>::traverse2(function<void (T)> visit)
{
    Pos(T) scan = _header; if(_size)
    {
        while((scan = scan->succ) != _trailer)
        {
            visit(scan->data); 
        } 
    }
}

template <typename T>
Pos(T) 
List<T>::search(const T &e, int n, Pos(T) p) const
{
    assert(0 <= n < _size); 
    while(0 <=n--)
    {
        if((p = p->pred)->data  <= e)
        {
            break;
        }
    } 
    return p;
}

template <typename T>
Pos(T) 
List<T>::search(const T &e) const
{
    return search(e, _size, _trailer);
}

template <typename T>
int
List<T>::uniquify()
{
    if(_size < 2)
        return 0;
    int oldsize = _size;
    Pos(T) curr = _header->succ; 
    Pos(T) succ = nullptr;
    while((succ = curr->succ) != _trailer)
    {
        if(succ->data == curr->data)
        {
            remove(succ);
        }
        else{
            curr = curr->succ; 
        }
    } 
    return oldsize - _size;
} 

template <typename T>
Pos(T) 
List<T>::bubble(Pos(T) low, Pos(T) high)
{
    Pos(T) last = low;
    while((low = low->succ)  != high)
    {
        if(low->data < low->pred->data)
        {
            last = low;
            std::swap(low->data, low->pred->data);    
        }
    }
    return last;
}


template <typename T>
void 
List<T>::bubbleSort(Pos(T) p, int n)
{
    Pos(T) high = p;
    while(n--)
        high = high->succ; 
    while(p != (high = bubble(p, high)));
}

/* 教材的版本
template <typename T>
void 
List<T>::insertSort(Pos(T) p, int n)
{
    Pos(T) scan = p;
    Pos(T) high = p;
    Pos(T) ret;
    while(n--)
        high = high->succ;  
    int r = 0;
    while(scan != high)
    {
        insertAfter(search(scan->data, r++, scan), scan->data); 
        scan = scan->succ;
        remove(scan->pred); 
    }
}*/
template <typename T>
void 
List<T>::insertSort(Pos(T) p, int n)
{
    Pos(T) scan = p;
    Pos(T) high = p;
    Pos(T) ret;
    Pos(T) sortedTail = p;
    while(n--)
        high = high->succ;  
    int r = 0;
    while((scan = sortedTail->succ)  != high)
    {
        if(scan->data < sortedTail->data)
        {  
            auto pos = search(scan->data, r++, scan); 
            insertAfter(pos, remove(scan)); 
        }
        else{
            sortedTail = sortedTail->succ;
            ++r; 
        }
    }
}

template <typename T>
void 
List<T>::selectSort(Pos(T) p, int n)
{
    Pos(T) high = p;
    while(n--)
        high = high->succ; 
    while(p != high)
    {
        std::swap(selectMax(p, high)->data , high->pred->data );
        high = high->pred; 
    }
}

template <typename T>
Pos(T) 
List<T>::selectMax(Pos(T) low, Pos(T) high)
{
    Pos(T) mx = low;
    while((low = low->succ) != high)
    {
        if(low->data >= mx->data)
          mx = low;  
    } 
    return mx;
}

template <typename T>
void 
List<T>::mergeSort(Pos(T) p, int n)
{
    if( n < 2 ) return ;
    Pos(T) p2 = p;
    int mid = n >> 1;
    int a = mid;
    while(a--) p2 = p2->succ; 
    mergeSort(p, mid);
    mergeSort(p2, n - mid);
    if(p2->pred->data > p2->data)
      merge(p, mid, n);  
}

template <typename T>
void
List<T>::merge(Pos(T) p, int mid, int n)
{
    int lenB = mid;
    int lenC = n - mid;
    Pos(T) A = p;
    T * B = new T[mid];
    for(int i = 0; i<mid; ++i)
    {
        B[i]= p->data;
        p = p->succ;  
    }
    Pos(T) C = p;
    for(int j = 0, k = 0; j < lenB;)
    {
        if( lenC <= k || B[j] <= C->data )
        {
            A->data = B[j++];  
            A = A->succ;
        }
        if( k < lenC && C->data < B[j])
        {
            A->data = C->data;  
            A = A->succ;
            C = C->succ; 
            ++k;
        }  
    }
    delete []B;
} 

template <typename T>
void 
List<T>::reverse()
{
    Pos(T) first = _header;
    Pos(T) second = _header->succ; 
    while(second != _trailer)
    {
        first->succ = first->pred;
        first->pred = second; 
        first = second;
        second = second->succ;   
    }
    first->succ = first->pred;
    first->pred = second; 
    _trailer->succ = _trailer->pred;
    _trailer->pred = nullptr;
    std::swap(_header, _trailer);   
}
template <typename T>
void 
List<T>::reverse2()
{
    Pos(T) p = _header;
    Pos(T) q = _header->succ; 
    while(p != _trailer)
    {
        p->pred = q;
        p = q;
        q = q->succ;  
    }
    _trailer->pred = nullptr;  
    p = _header;
    q = _header->succ;
    while(p != _trailer)
    {
        q->succ = p;
        p = q;
        q = p->pred;  
    } 
    _header->succ = nullptr; 
    std::swap(_header, _trailer); 
}

//交换指针
template <typename T>
void 
List<T>::reverse3()
{
    Pos(T) p = _header;
    for(; p; p = p->pred)
    {
        std::swap(p->pred, p->succ);
    }
    std::swap(_header, _trailer);     
}

// 交换数据
template <typename T>
void 
List<T>::reverse4()
{
    Pos(T) p = _header;
    Pos(T) q = _trailer;
    while(1)
    {
        p = p->succ;  
        if( p == q)
            break;
        q = q->pred;
        if( p == q)
            break;
        std::swap(p->data, q->data);    
    }
}
