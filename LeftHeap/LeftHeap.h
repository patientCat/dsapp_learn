#ifndef _LEFTHEAP_H_
#define _LEFTHEAP_H_

#include "BinTree.h" 

template <typename T>
class PQ_LeftHeap 
: public BinTree<T>
{ 
public: 
    using BinTree<T>::_root; 
    using BinTree<T>::_size; 
    PQ_LeftHeap () = default;
    // 批量构造
    PQ_LeftHeap (T *E, int n); 
    ~PQ_LeftHeap () = default; 
     
    void insert(T &e); // 按照比较器确定的优先级次序插入元素
    T getMax()  {   return _root->data; }  // 取出优先级最高的元素
    T delMax(); // 删除优先级最高的元素

    static BinNodePos(T) merge(BinNodePos(T) a, BinNodePos(T) b)
    {
        // 递归基的处理
        if(!a)  return b;
        if(!b)  return a;
        // 互换名字，保证a始终是顶点元素大的那个
        if( a->data < b->data) std::swap(a, b);    
        a->rc = merge(a->rc, b); 
        a->rc->parent = a;  
        if(!a->lc || a->lc->npl < a->rc->npl)
            std::swap(a->lc, a->rc);        
        a->npl = a->rc ? a->rc->npl + 1 : 1;
        return a;    
    }
private: 
}; 

template <typename T>
PQ_LeftHeap<T>::PQ_LeftHeap(T *E, int n)
{
    // 可以改进为 Floyd 建堆算法 
    for(int i = 0; i < n; ++i)
        insert(E[i]);
} 

template <typename T>
void
PQ_LeftHeap<T>::insert(T &e)
{
    BinNodePos(T) node = new BinNode<T>(e);
    _root = merge(_root, node);
    if(_root)
    _root->parent = nullptr; 
    ++_size;
}

template <typename T>
T
PQ_LeftHeap<T>::delMax()
{
    BinNodePos(T) temp = _root;
    _root = merge(_root->rc, _root->lc);  
    if(_root)
        _root->parent = nullptr; 
    T ret = temp->data; 
    delete temp;
    --_size;
    return ret;
} 

#endif /* LeftHeap_h */
